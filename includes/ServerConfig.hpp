#ifndef SERVERCONFIG_HPP
# define SERVERCONFIG_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <fstream>
# include <sstream>
# include "../srcs/errors/parsing/errors.cpp"

class ServerConfig
{
	private:
        std::vector<std::map<std::string, std::string> > m_servers;
		std::map<std::string, size_t> m_limits;
		std::vector<std::map<std::string, std::string> > m_locations;
		std::vector<size_t> m_cLocationServer;
	public:
		ServerConfig();
		ServerConfig(const ServerConfig &copy);
		~ServerConfig();
		ServerConfig& operator=(const ServerConfig& copy);
		void	tokenization(char *argv);
};

#endif
