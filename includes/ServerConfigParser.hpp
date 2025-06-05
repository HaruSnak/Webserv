#ifndef SERVERCONFIGPARSER_HPP
# define SERVERCONFIGPARSER_HPP

# include <iostream>
# include <string>
# include <cstring>
# include <vector>
# include <map>
# include <fstream>
# include <sstream>
# include "Webserv.hpp"
# include "ServerConfig.hpp"

class ServerConfigParser
{
	private:
		std::vector<ServerConfig> m_servers;
	public:
		ServerConfigParser();
		ServerConfigParser(const ServerConfigParser &copy);
		~ServerConfigParser();
		ServerConfigParser& operator=(const ServerConfigParser& copy);
		void	parseServerDirectives(std::stringstream &ss, ServerConfig &server);
		template<typename SetterFunc>
		void	parseAddDirectiveSimple(std::stringstream &ss, ServerConfig &server, SetterFunc setter, const std::string &directive);
		template<typename T1, typename T2>
		void parseDirectiveTwoValues(std::stringstream &ss, ServerConfig &server, 
						void (ServerConfig::*setter)(T1, T2), const std::string& directive);
		template<typename Container>
		void parseDirectiveMultipleValues(std::stringstream &ss, ServerConfig &server,
						void (ServerConfig::*adder)(const typename Container::value_type&), const std::string& directive);
};

# include "ServerConfigParser.tpp"

#endif