#ifndef LOCATIONCONFIG_HPP
# define LOCATIONCONFIG_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include "Webserv.hpp"

class LocationConfig
{
    private:
		std::string m_path;
		std::string m_root;
		std::string m_index;
		std::string m_upload;
		bool m_autoindex;
		std::vector<std::string> m_httpMethods;
		std::map<std::string, std::string> m_cgi;
    public:
        LocationConfig();
        LocationConfig(const LocationConfig &copy);
        ~LocationConfig();
        LocationConfig& operator=(LocationConfig& copy);
		void	addPath(const std::string &path);
		void	addRoot(const std::string &root);
		void	addIndex(const std::string &index);
		void	addUpload(const std::string &upload);
		void	addAutoIndex(const std::string &isAutoIndex);
		void	addHTTPMethods(const std::string &httpMethods);
		void	addCgi(const std::string index, const std::string &url);
		std::string getPath(void) const;
		std::string getRoot(void) const;
		std::string	getUpload(void) const;
		bool	getAutoIndex(void) const;
		std::string	getHTTPMethods(size_t index) const;
		std::string	getCGIHandler(const std::string &index) const;
		//delete tests
		const std::vector<std::string>& getHTTPMethods() const;
    	const std::map<std::string, std::string>& getCGI() const;
};

#endif
