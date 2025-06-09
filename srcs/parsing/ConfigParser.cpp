#include "../../includes/ConfigParser.hpp"

/*------------------------------- CONSTRUCTOR --------------------------------*/

ConfigParser::ConfigParser()
{
	std::cout << "ConfigParser constructor called" << std::endl;
	return ;
}

ConfigParser::ConfigParser(const ConfigParser &copy)
{
	std::cout << "ConfigParser constructor copy" << std::endl;
	*this = copy;
	return ;
}

/*------------------------------- DESTRUCTOR --------------------------------*/

ConfigParser::~ConfigParser()
{
	std::cout << "ConfigParser destructor called" << std::endl;
	return ;
}

/*------------------------------- OVERLOAD OPERATOR --------------------------------*/

ConfigParser& ConfigParser::operator=(const ConfigParser& copy)
{
	if (this != &copy)
	{
        this->m_serverConfig = copy.m_serverConfig;
        this->m_locationConfig = copy.m_locationConfig;
	}
	return (*this);
}

/*------------------------------- FUNCTIONS --------------------------------*/

void	ConfigParser::parseConfigFile(char *argv)
{
	std::ifstream file(argv);
	if (!file)
		errorTypeExt("File access problem or non-existent!", -1);
	std::vector<std::string> stack;
	std::string buff;
	std::string token;
	size_t c_index = 0;
	bool serverOn = false;
	while (std::getline(file, buff))
		stack.push_back(buff);
	file.close();
	for (; c_index < stack.size(); c_index++)
	{
		std::cout << "BASE BUFF: " << stack[c_index] << std::endl;
		std::stringstream ss(stack[c_index]);
		ss >> token;
		std::cout << "BASE: " << token << std::endl;
		if (!token.empty())
			continue ;
		if (token == "server" && ss >> token && token == "{")
		{
			serverOn = true;
			parseServerBlock(stack, c_index);
		}
		else
			errorTypeExt(" 1 - Unknown directive in configuration file!", -1);
		std::cout << c_index << std::endl;
	}
}

void	ConfigParser::parseServerBlock(const std::vector<std::string> &stack, size_t &c_index) // REWORK CODE ? BOOL CHECK SI UTILS
{
	ServerConfig newServer;
	//bool locationOn = false;
	c_index++;
	for (; c_index < stack.size(); c_index++)
	{
		std::stringstream ss(stack[c_index]);
		std::string token;
		ss >> token;
		std::cout << " 2 - BASE: " << token << std::endl;
		if (token == "}")
		{
			this->m_servers.push_back(newServer);
			c_index++;
			std::cout << "2 - BASE BUFF: " << stack[c_index] << std::endl;
			return ;
		}
		else if (token == "location")
		{
			if (ss >> token)
			{
				std::string path = token;
				if (ss >> token && token == "{")
				{
					//locationOn = true;
					parseLocationBlock(stack, newServer, path, c_index);
				}
				else
					errorTypeExt("Syntaxe incomplet !", -1);
			}
			else
					errorTypeExt("Syntaxe incomplet !", -1);
		}
		else
			m_serverConfig.parseServerDirectives(ss, newServer);
	}
}

void	ConfigParser::parseLocationBlock(const std::vector<std::string> &stack, ServerConfig &server, const std::string &path, size_t &c_index)
{
	LocationConfig newLocation;
	newLocation.addPath(path);
	c_index++;
	for (; c_index < stack.size(); c_index++)
	{
		std::stringstream ss(stack[c_index]);
		std::string token;
		ss >> token;
		if (token == "}")
		{
			server.addLocation(newLocation);
			break;
		}
		else
			m_locationConfig.parseLocationDirectives(ss, newLocation);
	}
}

/*------------------------------- TEST FUNCTIONS --------------------------------*/

void ConfigParser::printAllServers() const
{
    std::cout << "\n========== PARSING RESULTS ==========" << std::endl;
    std::cout << "Total servers found: " << m_servers.size() << std::endl;
    
    for (size_t i = 0; i < m_servers.size(); ++i)
    {
        std::cout << "\n--- SERVER " << i << " ---" << std::endl;
        printServerDetails(i);
    }
    std::cout << "====================================\n" << std::endl;
}

void ConfigParser::printServerDetails(size_t serverIndex) const
{
    if (serverIndex >= m_servers.size())
    {
        std::cout << "❌ Server index " << serverIndex << " out of range!" << std::endl;
        return;
    }
    
    const ServerConfig& server = m_servers[serverIndex];
    
    std::cout << "Listen: " << server.getListen() << std::endl;
    std::cout << "Server Name: " << server.getServerName() << std::endl;
    std::cout << "Root: " << server.getRoot() << std::endl;
    std::cout << "Index: " << server.getIndex() << std::endl;
    std::cout << "Client Max Body Size: " << server.getClientSize() << std::endl;
    std::cout << "Upload: " << server.getUpload() << std::endl;
    std::cout << "Autoindex: " << (server.getAutoIndex() ? "on" : "off") << std::endl;
    
    // HTTP Methods
    const std::vector<std::string>& methods = server.getHTTPMethods();
    std::cout << "HTTP Methods: ";
    for (size_t i = 0; i < methods.size(); ++i)
    {
        std::cout << methods[i];
        if (i < methods.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    
    // Error Pages
    const std::map<size_t, std::string>& errorPages = server.getErrorsPages();
    std::cout << "Error Pages:" << std::endl;
    for (std::map<size_t, std::string>::const_iterator it = errorPages.begin(); it != errorPages.end(); ++it)
    {
        std::cout << "  " << it->first << " -> " << it->second << std::endl;
    }
    
    // CGI
    const std::map<std::string, std::string>& cgi = server.getCgi();
    std::cout << "CGI:" << std::endl;
    for (std::map<std::string, std::string>::const_iterator it = cgi.begin(); it != cgi.end(); ++it)
    {
        std::cout << "  " << it->first << " -> " << it->second << std::endl;
    }
    
    // Locations
    const std::vector<LocationConfig>& locations = server.getLocations();
    std::cout << "Locations (" << locations.size() << "):" << std::endl;
    for (size_t i = 0; i < locations.size(); ++i)
    {
        std::cout << "\n  --- LOCATION " << i << " ---" << std::endl;
        printLocationDetails(serverIndex, i);
    }
}

void ConfigParser::printLocationDetails(size_t serverIndex, size_t locationIndex) const
{
    if (serverIndex >= m_servers.size())
    {
        std::cout << "❌ Server index out of range!" << std::endl;
        return;
    }
    
    const std::vector<LocationConfig>& locations = m_servers[serverIndex].getLocations();
    if (locationIndex >= locations.size())
    {
        std::cout << "❌ Location index out of range!" << std::endl;
        return;
    }
    
    const LocationConfig& location = locations[locationIndex];
    
    std::cout << "  Path: " << location.getPath() << std::endl;
    std::cout << "  Root: " << location.getRoot() << std::endl;
    std::cout << "  Upload: " << location.getUpload() << std::endl;
    std::cout << "  Autoindex: " << (location.getAutoIndex() ? "on" : "off") << std::endl;
    
    // HTTP Methods
    const std::vector<std::string>& methods = location.getHTTPMethods();
    std::cout << "  HTTP Methods: ";
    for (size_t i = 0; i < methods.size(); ++i)
    {
        std::cout << methods[i];
        if (i < methods.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    
    // CGI
    const std::map<std::string, std::string>& cgi = location.getCGI();
    std::cout << "  CGI:" << std::endl;
    for (std::map<std::string, std::string>::const_iterator it = cgi.begin(); it != cgi.end(); ++it)
    {
        std::cout << "    " << it->first << " -> " << it->second << std::endl;
    }
}

bool ConfigParser::validateParsing() const
{
    std::cout << "\n========== VALIDATION ==========" << std::endl;
    bool isValid = true;
    
    if (m_servers.empty())
    {
        std::cout << "❌ No servers found!" << std::endl;
        return false;
    }
    
    for (size_t i = 0; i < m_servers.size(); ++i)
    {
        const ServerConfig& server = m_servers[i];
        std::cout << "Validating server " << i << "..." << std::endl;
        
        // Vérifications obligatoires
        if (server.getListen().empty())
        {
            std::cout << "❌ Server " << i << ": Missing listen directive!" << std::endl;
            isValid = false;
        }
        
        if (server.getRoot().empty())
        {
            std::cout << "❌ Server " << i << ": Missing root directive!" << std::endl;
            isValid = false;
        }
        
        // Vérifications des locations
        const std::vector<LocationConfig>& locations = server.getLocations();
        for (size_t j = 0; j < locations.size(); ++j)
        {
            const LocationConfig& location = locations[j];
            if (location.getPath().empty())
            {
                std::cout << "❌ Server " << i << ", Location " << j << ": Missing path!" << std::endl;
                isValid = false;
            }
        }
        
        if (isValid)
            std::cout << "✅ Server " << i << " is valid" << std::endl;
    }
    
    if (isValid)
        std::cout << "✅ All servers are valid!" << std::endl;
    else
        std::cout << "❌ Some servers have errors!" << std::endl;
        
    std::cout << "==============================\n" << std::endl;
    return isValid;
}
