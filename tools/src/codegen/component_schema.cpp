#include <yaml-cpp/yaml.h>
#include "component_schema.h"

using namespace Halley;

ComponentSchema::ComponentSchema() {}

ComponentSchema::ComponentSchema(YAML::Node node)
{
	name = node["component"].as<std::string>();

	for (auto memberEntry : node["members"]) {
		for (auto m = memberEntry.begin(); m != memberEntry.end(); ++m) {
			members.emplace_back(VariableSchema(TypeSchema(m->second.as<std::string>()), m->first.as<std::string>()));
		}
	}
}
