#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <string>
# include <iostream>
# include <sstream>

namespace	color
{
	const std::string COLOR_RED = "\033[31m";
	const std::string COLOR_GREEN = "\033[32m";
	const std::string COLOR_NONE = "\033[0m";
	static inline std::ostream &red(const std::string &src)
	{
		return (std::cout << COLOR_RED << src << COLOR_NONE << std::endl);
	}
	static inline std::ostream &err_red(const std::string &src)
	{
		return (std::cerr << COLOR_RED << src << COLOR_NONE << std::endl);
	}
	static inline std::ostream &green(const std::string &src)
	{
		return (std::cout << COLOR_GREEN << src << COLOR_NONE << std::endl);
	}
	static inline std::ostream &err_green(const std::string &src)
	{
		return (std::cerr << COLOR_GREEN << src << COLOR_NONE << std::endl);
	}
}

void	excluding_token(std::stringstream& ss, std::string token);
void	errorTypeExt(std::string errorMsg, int n);

#endif
