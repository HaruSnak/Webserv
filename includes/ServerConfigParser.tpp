#include "ServerConfigParser.hpp"

template<typename SetterFunc>
void	ServerConfigParser::parseAddDirectiveSimple(std::stringstream &ss, ServerConfig &server, SetterFunc setter, const std::string &directive)
{
	std::string value;
	if (ss >> value)
	{
		if (value.back() == ';')
			value.pop_back();
		else
			errorTypeExt(directive + ": ';' missing at the end of a directive", -2);
		if (directive == "client_max_body_size")
		{
			size_t tmp = std::stoul(value);
			(server.*setter)(tmp);
		}
		else
			(server.*setter)(value);
	}
	else
		errorTypeExt(directive + ": Problem with this directive!", -1);
}

template<typename T1, typename T2>
void	ServerConfigParser::parseDirectiveTwoValues(std::stringstream &ss, ServerConfig &server, 
                    void (ServerConfig::*setter)(T1, T2), const std::string& directive)
{
    std::string value1, value2;
    if (!(ss >> value1 >> value2))
        errorTypeExt(directive + ": Missing values!", -1);
    if (value2.back() == ';')
        value2.pop_back();
	else
        errorTypeExt(directive + ": ';' missing at the end", -2);
    if (directive == "error_page")
	{
        int code = std::stoi(value1.c_str());
        (server.*setter)(code, value2);
    }
	else if (directive == "cgi")
        (server.*setter)(value1, value2);
}

template<typename Container>
void ServerConfigParser::parseDirectiveMultipleValues(std::stringstream &ss, ServerConfig &server,
                    void (ServerConfig::*adder)(const typename Container::value_type&), const std::string& directive)
{
    std::string value;
    bool foundSemicolon = false;
    
    while (ss >> value)
	{
        if (value.back() == ';')
		{
            value.pop_back();
            foundSemicolon = true;
            if (!value.empty())
                (server.*adder)(value);
			else
				errorTypeExt(directive + ": Problem with this directive!", -1);
            break;
        }
        (server.*adder)(value);
    }
    if (!foundSemicolon)
        errorTypeExt(directive + ": ';' missing at the end", -2);
}