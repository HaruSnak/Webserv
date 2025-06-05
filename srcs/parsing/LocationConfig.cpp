#include "../../includes/LocationConfig.hpp"

//------------------------------- CONSTRUCTOR --------------------------------/

LocationConfig::LocationConfig()
{
    std::cout << "Default constructor called" << std::endl;
}

LocationConfig::LocationConfig(const LocationConfig &copy)
{
    std::cout << "Name constructor called" << std::endl;
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

    }
    return (*this);
}

//------------------------------- FUNCTIONS --------------------------------*/

void	LocationConfig::addRoot(const std::string &root)
{
	this->m_root = root;
	return ;
}

void	LocationConfig::addUpload(const std::string &upload)
{
	this->m_upload = upload;
	return ;
}

void	LocationConfig::addAutoIndex(bool isAutoIndex)
{
	this->m_autoindex = isAutoIndex;
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