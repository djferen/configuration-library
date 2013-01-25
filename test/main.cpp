#include "Configuration.h"

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <qpid/types/Variant.h>
#include <qpid/management/ConnectionSettings.h>

int main( int argc, const char *argv[] )
{
	boost::shared_ptr<configuration::Configuration>
		config (new configuration::Configuration("main.cnf"));

	if(config->initialize())
	{
		qpid::types::Variant::Map configMap = config->getMap();

		std::cout << "Iterated over the whole map..." << std::endl;

		qpid::types::Variant::Map::const_iterator iter = configMap.begin();
		for(; iter != configMap.end(); iter++)
		{
			std::cout << iter->first << " = " << (iter->second).asString() << std::endl;
		}


		std::cout << "Now by path into a partial var map (effectively getting a sub-tree)..." << std::endl;

		qpid::types::Variant::Map partialMap;

		partialMap = config->getMap("qpidConnections.primary", partialMap);

		for(iter = partialMap.begin(); iter != partialMap.end(); iter++)
		{
			std::cout << iter->first << " = " << (iter->second).asString() << std::endl;
		}


		partialMap.clear();

		std::cout << "Now by 1st field..." << std::endl;

		partialMap = config->getMap("qpidConnections", partialMap);

		for(iter = partialMap.begin(); iter != partialMap.end(); iter++)
		{
			std::cout << iter->first << " = " << (iter->second).asString() << std::endl;
		}


		partialMap.clear();

		std::cout << "Now all of the map by blank path..." << std::endl;

		partialMap = config->getMap("", partialMap);

		for(iter = partialMap.begin(); iter != partialMap.end(); iter++)
		{
			std::cout << iter->first << " = " << (iter->second).asString() << std::endl;
		}


		std::cout << "Now a path found in the map..." << std::endl;

		config->print("qpidConnections.primary.options.heartbeat");

		std::cout << "Or by vector of paths in the map..." << std::endl;

		std::vector<std::string> paths;

		//Need to test
		//paths.push_back("");
		//paths.push_back("qpidConnections.primary.options.heartbeat");
		paths.push_back("qpidConnections.secondary.options.maxChannels");
		paths.push_back("qpidConnections.primary.options.heartbeat");

		config->print(paths);
	}
	else
	{
		std::cout << "Unable to initialize configuration" << std::endl;
	}

	return 0;
}

