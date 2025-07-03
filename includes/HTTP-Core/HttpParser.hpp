#ifndef HTTP_PARSER_HPP
#define HTTP_PARSER_HPP

#include <string>
#include <map>
#include <iostream>
#include <sstream>

class HttpRequest {
public:
	std::string method;
	std::string uri;
	std::string version;
	std::map<std::string, std::string> headers;
	std::string body;
	bool isComplete;
	bool isValid;
	
	HttpRequest() : isComplete(false), isValid(false) {}
	
	void print() const {
		std::cout << "Method: " << method << std::endl;
		std::cout << "URI: " << uri << std::endl;
		std::cout << "Version: " << version << std::endl;
		std::cout << "Headers:" << std::endl;
		
		for (std::map<std::string, std::string>::const_iterator it = headers.begin(); 
			 it != headers.end(); ++it) {
			std::cout << "  " << it->first << ": " << it->second << std::endl;
		}
		
		if (!body.empty()) {
			std::cout << "Body: " << body << std::endl;
		}
	}
};

class HttpParser {
private:
	std::string buffer;
	bool headersParsed;
	size_t contentLength;
	
	bool parseHeaders(const std::string& headerSection, HttpRequest& request);
	bool parseRequestLine(const std::string& line, HttpRequest& request);
	bool parseHeader(const std::string& line, HttpRequest& request);
	std::string trim(const std::string& str);
	bool isValidMethod(const std::string& method);

public:
	HttpParser();
	bool parse(const char* data, size_t length, HttpRequest& request);
	void reset();
	bool isRequestComplete(const HttpRequest& request);
};

#endif
