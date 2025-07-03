#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include "HttpParser.hpp"
#include "HttpResponse.hpp"
#include <string>

class RequestHandler {
private:
	std::string documentRoot;
	
	std::string getMimeType(const std::string& filename);
	std::string readFile(const std::string& filepath);
	bool fileExists(const std::string& filepath);
	std::string getErrorPage(int errorCode);

public:
	RequestHandler(const std::string& docRoot = "./www");
	
	// Méthodes principales selon le sujet webserv
	HttpResponse handleRequest(const HttpRequest& request);
	HttpResponse handleGet(const HttpRequest& request);
	HttpResponse handlePost(const HttpRequest& request);
	HttpResponse handleDelete(const HttpRequest& request);
	
	void setDocumentRoot(const std::string& root);
};

#endif
