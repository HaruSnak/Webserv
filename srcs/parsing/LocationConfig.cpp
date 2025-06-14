#include "../../includes/LocationConfig.hpp"

//------------------------------- CONSTRUCTOR --------------------------------/

LocationConfig::LocationConfig() :
m_path(""),
m_root(""),
m_index(""),
m_upload(""),
m_autoindex(false)
{
    std::cout << "Default constructor called" << std::endl;
	const char *directives[] = {
		"path", "root", "index", "http_methods", "cgi", "upload", "autoindex"
	};
	for (size_t i = 0; i < static_cast<size_t>(sizeof(directives) / sizeof(directives[0])); i++)
		this->m_hasDirective[static_cast<std::string>(directives[i])] = false;
	return ;
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
	this->m_hasDirective = copy.m_hasDirective;
	return ;
}

//------------------------------- DESTRUCTOR --------------------------------/

LocationConfig::~LocationConfig()
{
    std::cout << "Destructor called" << std::endl;
	return ;
}

//------------------------------- OVERLOAD OPERATOR --------------------------------/

LocationConfig& LocationConfig::operator=(const LocationConfig& copy)
{
    if (this != &copy)
    {
		this->m_path = copy.m_path;
		this->m_root = copy.m_root;
		this->m_upload = copy.m_upload;
		this->m_autoindex = copy.m_autoindex;
		this->m_httpMethods = copy.m_httpMethods;
		this->m_cgi = copy.m_cgi;
		this->m_hasDirective = copy.m_hasDirective;
    }
    return (*this);
}

//------------------------------- FUNCTIONS --------------------------------*/

void	LocationConfig::initCheckDirective(const std::string &directive, bool multipleDirective)
{
	if (!multipleDirective && this->m_hasDirective[directive])
	{
		errorTypeExt(directive + ": Multiple directive prohibited for this one!", -2);
	}
	this->m_hasDirective[directive] = true;
	return ;
}

void	LocationConfig::checkNeedDirective(void)
{
	if (!this->m_hasDirective["path"])
		errorTypeExt("If the Location block is empty, it must have at least its path", -2);
}

//------------------------------- SETTERS --------------------------------*/

void	LocationConfig::addPath(const std::string &path)
{
	if (!path.empty() && path[0] == '/')
		this->m_path = path;
	else
		errorTypeExt("location: invalid path!", -4);
	this->initCheckDirective("path", false);
	return ;
}

void	LocationConfig::addRoot(const std::string &root)
{
	this->m_root = root;
	this->initCheckDirective("root", false);
	return ;
}

void	LocationConfig::addIndex(const std::string &index)
{
	this->m_index = index;
	this->initCheckDirective("index", false);
	return ;
}

void	LocationConfig::addUpload(const std::string &upload)
{
	this->m_upload = upload;
	this->initCheckDirective("upload", false);
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
	this->initCheckDirective("autoindex", false);
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
	this->initCheckDirective("cgi", true);
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