#include "../../includes/HTTP-Core/RequestHandler.hpp"
#include <fstream>
#include <cstdio>
#include <sys/stat.h>

RequestHandler::RequestHandler(const std::string& docRoot) : documentRoot(docRoot) {
}

void RequestHandler::setDocumentRoot(const std::string& root) {
	documentRoot = root;
}

HttpResponse RequestHandler::handleRequest(const HttpRequest& request) {
	// Validation de base
	if (!request.isValid || !request.isComplete) {
		return HttpResponse::badRequest();
	}
	
	// Router selon la méthode HTTP (obligatoire selon sujet)
	if (request.method == "GET") {
		return handleGet(request);
	} else if (request.method == "POST") {
		return handlePost(request);
	} else if (request.method == "DELETE") {
		return handleDelete(request);
	} else {
		// Méthode non supportée
		return HttpResponse::methodNotAllowed();
	}
}

HttpResponse RequestHandler::handleGet(const HttpRequest& request) {
	std::string filepath = documentRoot + request.uri;
	
	// Sécurité : empêcher l'accès en dehors du document root
	if (request.uri.find("..") != std::string::npos) {
		return HttpResponse::badRequest();
	}
	
	// Si c'est un répertoire, chercher index.html
	struct stat st;
	if (stat(filepath.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
		if (filepath[filepath.length() - 1] != '/') {
			filepath += "/";
		}
		filepath += "index.html";
	}
	
	// Vérifier que le fichier existe
	if (!fileExists(filepath)) {
		return HttpResponse::notFound();
	}
	
	// Lire le fichier
	std::string content = readFile(filepath);
	if (content.empty()) {
		return HttpResponse::internalServerError();
	}
	
	// Créer la réponse avec le bon MIME type
	HttpResponse response = HttpResponse::ok(content);
	response.setContentType(getMimeType(filepath));
	
	return response;
}

HttpResponse RequestHandler::handlePost(const HttpRequest& request) {
	// Selon le sujet : support des uploads et traitement de données
	
	// Pour un upload simple (sans multipart pour l'instant)
	std::string uploadPath = documentRoot + "/uploads" + request.uri;
	
	// Créer le fichier avec le contenu du body
	std::ofstream file(uploadPath.c_str(), std::ios::binary);
	if (!file.is_open()) {
		return HttpResponse::internalServerError();
	}
	
	file.write(request.body.c_str(), request.body.length());
	file.close();
	
	// Retourner 201 Created
	return HttpResponse::created();
}

HttpResponse RequestHandler::handleDelete(const HttpRequest& request) {
	std::string filepath = documentRoot + request.uri;
	
	// Sécurité
	if (request.uri.find("..") != std::string::npos) {
		return HttpResponse::badRequest();
	}
	
	// Vérifier que le fichier existe
	if (!fileExists(filepath)) {
		return HttpResponse::notFound();
	}
	
	// Supprimer le fichier
	if (remove(filepath.c_str()) == 0) {
		return HttpResponse::noContent(); // 204 No Content
	} else {
		return HttpResponse::internalServerError();
	}
}

std::string RequestHandler::getMimeType(const std::string& filename) {
	size_t dotPos = filename.find_last_of('.');
	if (dotPos == std::string::npos) {
		return "application/octet-stream";
	}
	
	std::string extension = filename.substr(dotPos + 1);
	
	// MIME types basiques selon le sujet webserv
	if (extension == "html" || extension == "htm") return "text/html";
	if (extension == "css") return "text/css";
	if (extension == "js") return "application/javascript";
	if (extension == "json") return "application/json";
	if (extension == "txt") return "text/plain";
	if (extension == "jpg" || extension == "jpeg") return "image/jpeg";
	if (extension == "png") return "image/png";
	if (extension == "gif") return "image/gif";
	if (extension == "pdf") return "application/pdf";
	
	return "application/octet-stream";
}

std::string RequestHandler::readFile(const std::string& filepath) {
	std::ifstream file(filepath.c_str(), std::ios::binary);
	if (!file.is_open()) {
		return "";
	}
	
	// Lire tout le fichier
	file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	file.seekg(0, std::ios::beg);
	
	std::string content(size, '\0');
	file.read(&content[0], size);
	file.close();
	
	return content;
}

bool RequestHandler::fileExists(const std::string& filepath) {
	struct stat st;
	return (stat(filepath.c_str(), &st) == 0 && S_ISREG(st.st_mode));
}
