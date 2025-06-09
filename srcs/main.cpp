#include "../includes/Webserv.hpp"
#include "../includes/ConfigParser.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }
    
    try
    {
        ConfigParser parser;
        
        // ✅ PARSING
        std::cout << "🔄 Starting parsing..." << std::endl;
        parser.parseConfigFile(argv[1]);
        std::cout << "✅ Parsing completed!" << std::endl;
        
        // ✅ AFFICHAGE DES RÉSULTATS
        parser.printAllServers();
        
        // ✅ VALIDATION
        if (parser.validateParsing())
        {
            std::cout << "🎉 Configuration is valid and ready to use!" << std::endl;
        }
        else
        {
            std::cout << "❌ Configuration has errors!" << std::endl;
            return 1;
        }
        
        // ✅ TESTS SPÉCIFIQUES (optionnel)
        std::cout << "\n--- SPECIFIC TESTS ---" << std::endl;
        if (parser.getServerCount() > 0)
        {
            std::cout << "First server details:" << std::endl;
            parser.printServerDetails(0);
            
            if (parser.getServers()[0].getLocations().size() > 0)
            {
                std::cout << "\nFirst location of first server:" << std::endl;
                parser.printLocationDetails(0, 0);
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
