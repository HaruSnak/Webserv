#ifndef SERVERCONFIG_HPP
# define SERVERCONFIG_HPP

# include <iostream>
# include <string>
# include <map>
# include <vector>

class ServerConfig
{
	private:
		std::string m_listen;
		std::string m_server_name;
		std::string m_root;
		std::string m_index;
		size_t m_client_max_size;
		std::map<size_t, std::string> m_errorsPages;
		std::vector<std::string> m_httpMethods;
		std::map<std::string, std::string> m_cgi;
		std::string m_upload;
		bool m_autoindex;
		//std::map<std::string, bool> hasDirective;
	public:
		ServerConfig();
		ServerConfig(const ServerConfig &copy);
		~ServerConfig();
		ServerConfig& operator=(const ServerConfig& copy);
		void	addListen(const std::string &listen);
		void	addServerName(const std::string &serverName);
		void	addRoot(const std::string &root);
		void	addIndex(const std::string &index);
		void	addClientSize(size_t client_size);
		void	addErrorsPages(size_t code, const std::string &url);
		void	addHTTPMethods(const std::string &httpMethods);
		void	addCgi(const std::string index, const std::string &url);
		void	addUpload(const std::string &upload);
		void	addAutoIndex(bool isAutoIndex);
		std::string	getListen(void) const;
		std::string	getServerName(void) const;
		std::string getRoot(void) const;
		std::string getIndex(void) const;
		size_t getClientSize(void) const;
		std::map<size_t, std::string>::const_iterator getErrorsPages(size_t code) const;
		std::string	getHTTPMethods(size_t index) const;
		std::string	getCGIHandler(const std::string &index) const;
		std::string	getUpload(void) const;
		bool	getAutoIndex(void) const;
};

#endif
