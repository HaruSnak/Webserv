#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <set>
# include "../parsing/ConfigParser.hpp"

class WebServ
{
	private:
		std::vector<ServerConfig> m_servers;
		std::vector<int> m_sockets;
		std::map<int, std::vector<ServerConfig*> > m_socketToServer;
		void	setupSocket(void);
		ServerConfig* resolveServer(const std::string &host, int socket);
		LocationConfig* resolveLocation(const std::string &uri, ServerConfig server);
		std::string buildPath(const std::string &uri, LocationConfig *location, ServerConfig *server);

	public:
		WebServ();
		WebServ(const WebServ &copy);
		~WebServ();
		WebServ& operator=(const WebServ& copy);
		int	createSocket(ServerConfig &server);
		// getters
		std::vector<ServerConfig*>	getServerBySocket(int socket);
		std::string getMime(const std::string &uri);
		int	getStatusError(const std::string &uri, const std::string &method, LocationConfig *location, ServerConfig *server);
};

#endif
