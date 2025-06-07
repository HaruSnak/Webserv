#include "../../includes/ServerConfig.hpp"

/*------------------------------- CONSTRUCTOR --------------------------------*/

ServerConfig::ServerConfig()
{
	std::cout << "ServerConfig constructor called" << std::endl;
	this->m_upload = false;
	/*this->hasDirective["listen"] = false;
	this->hasDirective["server_name"] = false;
	this->hasDirective["root"] = false;
	this->hasDirective["index"] = false;
	this->hasDirective["client_max_body_size"] = false;
	this->hasDirective["error_page"] = false;
	this->hasDirective["http_methods"] = false;
	this->hasDirective["cgi"] = false;
	this->hasDirective["upload"] = false;
	this->hasDirective["autoindex"] = false;*/
	return ;
}

ServerConfig::ServerConfig(const ServerConfig &copy)
{
	std::cout << "ServerConfig constructor copy" << std::endl;
	*this = copy;
	return ;
}

/*------------------------------- DESTRUCTOR --------------------------------*/

ServerConfig::~ServerConfig()
{
	std::cout << "ServerConfig destructor called" << std::endl;
	return ;
}

/*------------------------------- OVERLOAD OPERATOR --------------------------------*/

ServerConfig& ServerConfig::operator=(const ServerConfig& copy)
{
	if (this != &copy)
	{
        this->m_listen = copy.m_listen;
        this->m_server_name = copy.m_server_name;
        this->m_root = copy.m_root;
        this->m_index = copy.m_index;
        this->m_client_max_size = copy.m_client_max_size;
        this->m_errorsPages = copy.m_errorsPages;
        this->m_httpMethods = copy.m_httpMethods;
        this->m_cgi = copy.m_cgi;
        this->m_upload = copy.m_upload;
        this->m_autoindex = copy.m_autoindex;
	}
	return (*this);
}

/*------------------------------- FUNCTIONS --------------------------------*/

void	ServerConfig::addListen(const std::string &listen)
{
	for (size_t i = 0; i < listen.length(); i++)
	{
		if (!std::isdigit(listen[i]) || i != '.' || i != ':')
			errorTypeExt("listen: Your IP address is not in the correct format. (Example: 111.111.111:8080)", -3);
	}
	this->m_listen = listen;
	return ;
}

void	ServerConfig::addServerName(const std::string &serverName)
{
	this->m_server_name = serverName;
	return ;
}

void	ServerConfig::addRoot(const std::string &root)
{
	this->m_root = root;
	return ;
}

void	ServerConfig::addIndex(const std::string &index)
{
	this->m_index = index;
	return ;
}

void	ServerConfig::addClientSize(std::string client_size)
{
	for (size_t i = 0; i < client_size.length(); i++)
	{
		if (!std::isdigit(client_size[i]))
			errorTypeExt("client_max_body_size: Only numbers possible (Min: 1024 <-> Max: 104857600)", -3);
	}
	size_t tmp = std::stoul(client_size);
	if (tmp < MIN_CLIENT_SIZE || tmp > MAX_CLIENT_SIZE)
		errorTypeExt("client_max_body_size: Number limit = Min: 1024 <-> Max: 104857600", -3);
	this->m_client_max_size = tmp;
	return ;
}

void	ServerConfig::addErrorsPages(size_t code, const std::string &url)
{
	this->m_errorsPages[code] = url;
	return ;
}

void	ServerConfig::addHTTPMethods(const std::string &httpMethods)
{
	this->m_httpMethods.push_back(httpMethods);
	return ;
}

void	ServerConfig::addCgi(const std::string index, const std::string &url)
{
	this->m_cgi[index] = url;
	return ;
}

void	ServerConfig::addUpload(const std::string &upload)
{
	this->m_upload = upload;
	return ;
}

void	ServerConfig::addAutoIndex(std::string isAutoIndex)
{
	if (isAutoIndex == "on")
		this->m_autoindex = true;
	else if (isAutoIndex == "off")
		this->m_autoindex = false;
	else
		errorTypeExt("autoindex: Invalid input (on or off)!", -4);
	return ;
}

void	ServerConfig::addLocation(const LocationConfig &location)
{
	this->m_locations.push_back(location);
}

std::string	ServerConfig::getListen(void) const
{
	return (this->m_listen);
}

std::string	ServerConfig::getServerName(void) const
{
	return (this->m_server_name);
}

std::string ServerConfig::getRoot(void) const
{
	return (this->m_root);
}

std::string ServerConfig::getIndex(void) const
{
	return (this->m_index);
}

size_t ServerConfig::getClientSize(void) const
{
	return (this->m_client_max_size);
}

std::map<size_t, std::string>::const_iterator ServerConfig::getErrorsPages(size_t code) const
{
	return (this->m_errorsPages.find(code));
}

std::string	ServerConfig::getHTTPMethods(size_t index) const
{
	return (this->m_httpMethods[index]);
}

std::string	ServerConfig::getCGIHandler(const std::string &index) const
{
	std::map<std::string, std::string>::const_iterator it = this->m_cgi.find(index);
	return (it != this->m_cgi.end() ? it->second : "");
}

std::string	ServerConfig::getUpload(void) const
{
	return (this->m_upload);
}

bool	ServerConfig::getAutoIndex(void) const
{
	return (this->m_autoindex);
}
