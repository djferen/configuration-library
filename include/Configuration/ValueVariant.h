#ifndef VALUEVARIANT_H_
#define VALUEVARIANT_H_

#include <jsoncpp/json.h>
#include <qpid/types/Variant.h>

namespace configuration {

qpid::types::Variant::Map & Convert(const std::string & name, const Json::Value & from, qpid::types::Variant::Map & to);

} /* namespace configuration */

#endif /* VALUEVARIANT_H_ */
