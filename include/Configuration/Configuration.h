#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <qpid/types/Variant.h>
#include <string>
#include <vector>

namespace configuration
{

class Configuration
{
public:
	Configuration(const std::string & file);
	~Configuration(){}

	bool initialize();

	// Obtains the whole configuration
	const qpid::types::Variant::Map & getMap();

	// Obtain a variant map from the Configuration map at or below a path
	// "" gets the whole configuraiton
	// qpidConnections gets the qpidConnections configuration data
	// qpidConnections.primary gets the primary qpidConnection data
	qpid::types::Variant::Map & getMap(const char * path, qpid::types::Variant::Map & partialMap);
	qpid::types::Variant::Map & getMap(const std::string & path, qpid::types::Variant::Map & partialMap);

	// Prints the configuration (at or below a path(s)) to std::out
	// "" prints the whole configuration
	// or prints the configuration based on path
	void print(const char * path);
	void print(const std::string & path);
	void print(const std::vector<std::string> & paths);

	// Obtains a partial map based off of regex
	// query("qpidConnections.*.options");
	// query("qpidConnections.*.URIs.*");
	//qpid::types::Variant::Map & query(const char * search, qpid::types::Variant::Map & partialMap);
	//qpid::types::Variant::Map & query(const std::string search, qpid::types::Variant::Map & partialMap);

private:

	qpid::types::Variant::Map m_ConfigMap;
	std::string m_fileName;
};


}

#endif /* CONFIGURATION_H_ */
