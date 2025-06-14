#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

# include <iostream>
# include <string>
# include "ServerConfigParser.hpp"
# include "LocationConfigParser.hpp"

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
		void	parseServerBlock(const std::vector<std::string> &stack, size_t &c_index, bool &serverOn);
		void	parseLocationBlock(const std::vector<std::string> &stack, ServerConfig &server, const std::string &path, size_t &c_index, bool &locationOn);
		// delete function tests
		void printAllServers() const;
		void printServerDetails(size_t serverIndex) const;
		void printLocationDetails(size_t serverIndex, size_t locationIndex) const;
		bool validateParsing() const;
		
		// Getters pour les tests
		const std::vector<ServerConfig>& getServers() const { return m_servers; }
		size_t getServerCount() const { return m_servers.size(); }
};

#endif