#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <string>

class WebServ
{
	private:

	public:
		WebServ();
		WebServ(const WebServ &copy);
		~WebServ();
		WebServ& operator=(const WebServ& copy);
};

#endif
