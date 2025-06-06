#include "GenericConfigParser.hpp"

template <typename ConfigType>
template<typename SetterFunc>
void	GenericConfigParser<ConfigType>::parseAddDirectiveSimple(std::stringstream &ss, ConfigType &config, SetterFunc setter, const std::string &directive)
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
			(config.*setter)(tmp);
		}
		else
			(config.*setter)(value);
	}
	else
		errorTypeExt(directive + ": Problem with this directive!", -1);
}

template <typename ConfigType>
template<typename T1, typename T2>
void	GenericConfigParser<ConfigType>::parseDirectiveTwoValues(std::stringstream &ss, ConfigType &config, 
					void (ConfigType::*setter)(T1, T2), const std::string& directive)
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
		for (size_t i = 0; i < value1.length(); i++)
		{
			if (!std::isdigit(value1[i]))
				errorTypeExt("client_max_body_size: Only numbers possible (Min: 1024 <-> Max: 104857600)", -3);
		}
        int code = std::stoi(value1.c_str());
        (config.*setter)(code, value2);
    }
	else if (directive == "cgi")
        (config.*setter)(value1, value2);
}
template <typename ConfigType>
template<typename Container>
void GenericConfigParser<ConfigType>::parseDirectiveMultipleValues(std::stringstream &ss, ConfigType &config,
					void (ConfigType::*adder)(const typename Container::value_type&), const std::string& directive)
{
    std::string value;
    bool foundSemicolon = false;
    
    while (ss >> value)
	{
        if (value.back() == ';')
		{
            value.pop_back();
            foundSemicolon = true;
            if (!value.empty() && (value == "GET" || value == "POST" || value == "DELETE"))
                (config.*adder)(value);
			else
				errorTypeExt(directive + ": Problem with this directive!", -1);
            break;
        }
		if (value == "GET" || value == "POST" || value == "DELETE")
        	(config.*adder)(value);
    }
    if (!foundSemicolon)
        errorTypeExt(directive + ": ';' missing at the end", -2);
}
