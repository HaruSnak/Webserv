#include "../../includes/LocationConfig.hpp"

//------------------------------- CONSTRUCTOR --------------------------------/

LocationConfig::LocationConfig()
{
    std::cout << "Default constructor called" << std::endl;
}

LocationConfig::LocationConfig(const LocationConfig &copy)
{
    std::cout << "Name constructor called" << std::endl;
	this->m_path = copy.m_path;
	this->m_root = copy.m_root;
	this->m_upload = copy.m_upload;
	this->m_autoindex = copy.m_autoindex;
	this->m_httpMethods = copy.m_httpMethods;
	this->m_cgi = copy.m_cgi;
	return ;
}

//------------------------------- DESTRUCTOR --------------------------------/

LocationConfig::~LocationConfig()
{
    std::cout << "Destructor called" << std::endl;
}

//------------------------------- OVERLOAD OPERATOR --------------------------------/

LocationConfig& LocationConfig::operator=(LocationConfig& copy)
{
    if (this != &copy)
    {
		this->m_path = copy.m_path;
		this->m_root = copy.m_root;
		this->m_upload = copy.m_upload;
		this->m_autoindex = copy.m_autoindex;
		this->m_httpMethods = copy.m_httpMethods;
		this->m_cgi = copy.m_cgi;
    }
    return (*this);
}

//------------------------------- FUNCTIONS --------------------------------*/

//------------------------------- SETTERS --------------------------------*/

void	LocationConfig::addPath(const std::string &path)
{
	if (!path.empty() && path[0] == '/')
		this->m_root = path;
	else
		errorTypeExt("location: invalid path!", -4);
	return ;
}

void	LocationConfig::addRoot(const std::string &root)
{
	this->m_root = root;
	return ;
}

void	LocationConfig::addIndex(const std::string &index)
{
	this->m_index = index;
	return ;
}

void	LocationConfig::addUpload(const std::string &upload)
{
	this->m_upload = upload;
	return ;
}

void	LocationConfig::addAutoIndex(const std::string &isAutoIndex)
{
	if (isAutoIndex == "on")
		this->m_autoindex = true;
	else if (isAutoIndex == "off")
		this->m_autoindex = false;
	else
		errorTypeExt("autoindex: Invalid input (on or off)!", -4);
	return ;
}

void	LocationConfig::addHTTPMethods(const std::string &httpMethods)
{
	this->m_httpMethods.push_back(httpMethods);
	return ;
}

void	LocationConfig::addCgi(const std::string index, const std::string &url)
{
	this->m_cgi[index] = url;
	return ;
}

//------------------------------- GETTERS --------------------------------*/

std::string LocationConfig::getPath(void) const
{
	return (this->m_path);
}

std::string LocationConfig::getRoot(void) const
{
	return (this->m_root);
}

std::string	LocationConfig::getUpload(void) const
{
	return (this->m_upload);
}

bool	LocationConfig::getAutoIndex(void) const
{
	return (this->m_autoindex);
}

std::string	LocationConfig::getHTTPMethods(size_t index) const
{
	return (this->m_httpMethods[index]);
}

std::string	LocationConfig::getCGIHandler(const std::string &index) const
{
	std::map<std::string, std::string>::const_iterator it = this->m_cgi.find(index);
	return (it != this->m_cgi.end() ? it->second : "");
}

// delete tests
const std::vector<std::string>& LocationConfig::getHTTPMethods() const
{
    return this->m_httpMethods;
}

const std::map<std::string, std::string>& LocationConfig::getCGI() const
{
    return this->m_cgi;
}