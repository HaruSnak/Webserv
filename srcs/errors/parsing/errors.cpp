#include "../../../includes/Webserv.hpp"

void	excluding_token(std::stringstream& ss, std::string token) // msg custom ?
{
	if (ss >> token && !ss.eof())
	{
		std::cerr << "Error: 1!" << std::endl;
		std::exit(-1);
	}
}

void	errorTypeExt(std::string errorMsg, int n)
{
	color::err_red("Error: " + errorMsg);
	std::exit(n);
}