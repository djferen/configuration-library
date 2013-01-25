#include "ValueVariant.h"

#include <vector>
#include <string>
#include <sstream>

namespace configuration {

qpid::types::Variant::Map & Convert(const std::string & field, const Json::Value & from, qpid::types::Variant::Map & to){

	if(from.type() == Json::objectValue)
	{
		std::vector<std::string> members = from.getMemberNames();
		std::vector<std::string>::const_iterator iter = members.begin();
		for(; iter != members.end(); iter++)
		{
			std::string newField = (field == "") ? *iter : field + "." + *iter;
			Convert(newField, from[*iter], to);
		}
	}
	else if(from.type() == Json::arrayValue)
	{
		for ( unsigned int index = 0; index < from.size(); ++index )
		{
			std::ostringstream newField;
			newField << field << "[" << index << "]";
			Convert(newField.str(), from[index], to);
		}
	}
	else if(from.type() == Json::intValue)
	{
		std::pair<std::string, qpid::types::Variant> pair (field, qpid::types::Variant(from.asInt()));
		to.insert( pair );
	}
	else if(from.type() == Json::stringValue)
	{
		std::pair<std::string, qpid::types::Variant> pair (field, qpid::types::Variant(from.asString()));
		to.insert( pair );
	}
	else if(from.type() == Json::booleanValue)
	{
		std::pair<std::string, qpid::types::Variant> pair (field, qpid::types::Variant(from.asBool()));
		to.insert( pair );
	}
	else if(from.type() == Json::realValue)
	{
		std::pair<std::string, qpid::types::Variant> pair (field, qpid::types::Variant(from.asDouble()));
		to.insert( pair );
	}
	else if(from.type() == Json::uintValue)
	{
		std::pair<std::string, qpid::types::Variant> pair (field, qpid::types::Variant(from.asUInt()));
		to.insert( pair );
	}
	else if(from.type() == Json::nullValue)
	{
		std::pair<std::string, qpid::types::Variant> pair (field, qpid::types::Variant());
		to.insert( pair );
	}

	return to;
}

} /* namespace configuration */
