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
	bool serverOn = false;
	bool locationOn = false;
	if (!file)
		errorTypeExt("File access problem or non-existent!", -1);
	std::string buff;
	std::string token;
	while (std::getline(file, buff))
	{
		std::stringstream ss(buff);
		ss >> token;
		if (token == "server" && ss >> token && token == "{")
			parseServerBlock(file);
		else
			errorTypeExt("Unknown directive in configuration file!", -1);

	}
	if (serverOn)
		errorTypeExt("{", -2);
		// Cas Erreur pour tout les cas de configs
		// Function qui check tout ce qui est obligatoire
	file.close();
}

void	ConfigParser::parseServerBlock(std::ifstream &file)
{
	ServerConfig newServer;
	std::string buff;
	while (std::getline(file, buff))
	{
		std::stringstream ss(buff);
		std::string token;
		ss >> token;
		if (token == "}")
		{
			this->m_servers.push_back(newServer);
			break;
		}
		else if (token == "location")
		{
			ss >> token;
			if (ss >> token && token == "{")
			{

			}
			else
				errorTypeExt("Syntaxe incomplet !", -1);
		}
		else
			m_serverConfig.parseServerDirectives(ss, newServer);
	}
}
