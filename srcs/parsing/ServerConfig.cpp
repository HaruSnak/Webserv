#include "../../includes/ServerConfig.hpp"

/*------------------------------- CONSTRUCTOR --------------------------------*/

ServerConfig::ServerConfig()
{
	std::cout << "ServerConfig constructor called" << std::endl;
	m_limits.insert({"server", 2});
	m_limits.insert({"listen", 2});
	m_limits.insert({"server_name", 2});
	m_limits.insert({"root", 2});
	m_limits.insert({"index", 2});
	m_limits.insert({"client_max_body_size", 2});
	m_limits.insert({"error_page", 3});
	m_limits.insert({"http_methods", 4});
	m_limits.insert({"cgi", 3});
	m_limits.insert({"upload", 2});
	m_limits.insert({"autoindex", 2});
	m_limits.insert({"location", 3});
	m_limits.insert({"return", 2});
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
		*this = copy;
	}
	return (*this);
}

/*------------------------------- FUNCTIONS --------------------------------*/

void	ServerConfig::tokenization(char *argv)
{
	std::ifstream file(argv);
	bool serverOn = false;
	bool locationOn = false;
	int i = 0; // size_t possible
	size_t locationCount = 0;
	size_t serverCount = 0;
	if (!file)
		errorTypeExt("File access problem or non-existent!", -1);
	std::string buff;
	while (std::getline(file, buff))
	{
		std::stringstream ss(buff);
		std::string token;
		while (ss >> token)
		{
			if (!serverOn)
			{
				if (token == "server")
				{
					if (ss >> token && token == "{")
					{
						serverOn = true;
						i++;
						excluding_token(ss, token);
					}
				}
				else
					excluding_token(ss, token); // peut-etre un bug & referencement
			}
			else
			{
				if (serverOn && !locationOn && token == "}")
				{
					excluding_token(ss, token);
					serverOn = false;
					serverCount++;
					this->m_cLocationServer.push_back(locationCount);
					locationCount = 0;
				}
				else if (serverOn && locationOn && token == "}")
				{
					excluding_token(ss, token);
					locationOn = false;
					locationCount++;
				}
				i++;
				if (i == 1 && this->m_limits.find(token) != this->m_limits.end()
				&& token != "error_page" && token != "http_methods" && token != "cgi")
				{
					std::string tmp_key = token;
					if (ss >> token)
					{
						if (token.back() == ';')
						{
							token.pop_back();
							this->m_servers[serverCount][tmp_key] = token;
						}
						else
						{
							std::string tmp_value = token;
							if (ss >> token && token == ";")
							{
								this->m_servers[serverCount][tmp_key] = token;
							}
						}
					}
					else
						errorTypeExt("Missing value", -2);
				}
			}
		}
	}
	if (serverOn)
		errorTypeExt("{", -2);
		// Cas Erreur pour tout les cas de configs
		// Function qui check tout ce qui est obligatoire
	file.close();
}
