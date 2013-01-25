#include <ValueVariant.h>
#include <Configuration.h>

#include <fstream>
#include <iostream>
#include <string>

#include <boost/algorithm/string/predicate.hpp>
//#include <boost/regex.hpp>

namespace configuration
{

Configuration::Configuration(const std::string & filename) : m_fileName(filename)
{

}

bool Configuration::initialize()
{
	std::ifstream is( m_fileName.c_str() );

	if(!is.is_open())
	{
		std::cout << "Failed to open " << m_fileName << std::endl;
		return false;
	}

	Json::Reader reader;
	Json::Value root;

	bool parsingSuccessful = reader.parse( is, root );
	if ( !parsingSuccessful )
	{
		// report to the user the failure and their locations in the document.
		std::cout  << "Failed to parse configuration\n"
				   << reader.getFormatedErrorMessages();
		return false;
	}

	is.close();

	m_ConfigMap = configuration::Convert(std::string(""), root, m_ConfigMap);

	return true;
}

const qpid::types::Variant::Map & Configuration::getMap()
{
	return this->m_ConfigMap;
}

//static void print(qpid::types::Variant::Map & varMap, const char * path);
void Configuration::print(const char * path)
{
	std::cout << path << " = " << this->m_ConfigMap[path] << std::endl;
}


void Configuration::print(const std::string & path)
{
	print(path.c_str());
}


void Configuration::print(const std::vector<std::string> & paths)
{
	std::vector<std::string>::const_iterator iter = paths.begin();
	for(; iter != paths.end(); iter++)
	{
		std::cout << *iter << " = " << this->m_ConfigMap[*iter] << std::endl;
	}
}


qpid::types::Variant::Map & Configuration::getMap(const char * path, qpid::types::Variant::Map & partialMap)
{
	return getMap((std::string)path, partialMap);
}


qpid::types::Variant::Map & Configuration::getMap(const std::string & path, qpid::types::Variant::Map & partialMap)
{
	qpid::types::Variant::Map::const_iterator iter = m_ConfigMap.begin();
	for(; iter != m_ConfigMap.end(); iter++)
	{
		if(boost::starts_with(iter->first, path))
		{
			std::pair<std::string, qpid::types::Variant> pair (iter->first, iter->second);
			partialMap.insert(pair);
		}
	}

	return partialMap;
}

/*
qpid::types::Variant::Map & Configuration::query(const char * search, qpid::types::Variant::Map & partialMap)
{
	return query((std::string)search, partialMap);
}


// Obtains a partial map based off of regex
// query("qpidConnections.*.options");
// query("qpidConnections.*.URIs.*");
qpid::types::Variant::Map & Configuration::query(const std::string search, qpid::types::Variant::Map & partialMap)
{
	boost::regex expression(search);

	qpid::types::Variant::Map::const_iterator iter = m_ConfigMap.begin();
	for(; iter != m_ConfigMap.end(); iter++)
	{
		boost::match_results<std::string::const_iterator> results;
		//if(boost::regex_match(iter->first, results, expression, boost::match_default | boost::match_partial))
		if(boost::regex_match(iter->first, expression, boost::match_default | boost::match_partial))
		{
			std::cout << "Result: " << iter->first << std::endl;
		}
	}

	return partialMap;
}
*/

}

