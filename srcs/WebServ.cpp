#include "../includes/WebServ.hpp"

/*------------------------------- CONSTRUCTOR --------------------------------*/

WebServ::WebServ()
{
	std::cout << "WebServ constructor called" << std::endl;
	return ;
}

WebServ::WebServ(const WebServ &copy)
{
	std::cout << "WebServ constructor copy" << std::endl;
	*this = copy;
	return ;
}

/*------------------------------- DESTRUCTOR --------------------------------*/

WebServ::~WebServ()
{
	std::cout << "WebServ destructor called" << std::endl;
	return ;
}

/*------------------------------- OVERLOAD OPERATOR --------------------------------*/

WebServ& WebServ::operator=(const WebServ& copy)
{
	if (this != &copy)
	{
		*this = copy;
	}
	return (*this);
}

/*------------------------------- FUNCTIONS --------------------------------*/



