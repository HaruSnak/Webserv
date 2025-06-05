#include "../../includes/LocationConfigParser.hpp"

/*------------------------------- CONSTRUCTOR --------------------------------*/

LocationConfigParser::LocationConfigParser()
{
	std::cout << "LocationConfigParser constructor called" << std::endl;
	return ;
}

LocationConfigParser::LocationConfigParser(const LocationConfigParser &copy)
{
	std::cout << "LocationConfigParser constructor copy" << std::endl;
	*this = copy;
	return ;
}

/*------------------------------- DESTRUCTOR --------------------------------*/

LocationConfigParser::~LocationConfigParser()
{
	std::cout << "LocationConfigParser destructor called" << std::endl;
	return ;
}

/*------------------------------- OVERLOAD OPERATOR --------------------------------*/

LocationConfigParser& LocationConfigParser::operator=(const LocationConfigParser& copy)
{
	if (this != &copy)
	{
		*this = copy;
	}
	return (*this);
}

/*------------------------------- FUNCTIONS --------------------------------*/



