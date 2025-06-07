#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

# include <iostream>
# include <string>
# include <ServerConfigParser.hpp>
# include <LocationConfigParser.hpp>

class ConfigParser
{
	private:
		ServerConfigParser m_serverConfig;
		LocationConfigParser m_locationConfig;
		std::vector<ServerConfig> m_servers;
	public:
		ConfigParser();
		ConfigParser(const ConfigParser &copy);
		~ConfigParser();
		ConfigParser& operator=(const ConfigParser& copy);
		void	parseConfigFile(char *argv);
		void	parseServerBlock(std::ifstream &file);
		void	parseLocationBlock(std::ifstream &file, ServerConfig &server);
};

#endif