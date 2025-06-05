#ifndef LOCATIONCONFIGPARSER_HPP
# define LOCATIONCONFIGPARSER_HPP

# include <iostream>
# include <string>

class LocationConfigParser
{
	private:

	public:
		LocationConfigParser();
		LocationConfigParser(const LocationConfigParser &copy);
		~LocationConfigParser();
		LocationConfigParser& operator=(const LocationConfigParser& copy);
};

#endif
