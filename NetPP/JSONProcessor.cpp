#include "include.h"


Package * JSONProcessor::ProcessPackage(std::string filepath)
{
	json json;

	std::ifstream i(filepath, std::ios::in);
	i >> json;

	std::string package_name;
	if (json["__pack"] != nullptr)
		package_name = json["__pack"].get<std::string>();
	else
		throw std::string("Attribute __pack not specified");

	int package_id = -1;
	if (json["__id"] != nullptr && json["__id"].is_number_integer())
		package_id = json["__id"].get<int>();
	else
		Console::Info("Attribute __id invalid or not specified -- We will generate it automatically");

	Package * pack;
	if (package_id < 0)
		pack = new Package(package_name);
	else
		pack = new Package(package_name, package_id);


	/* fetch attributes */

	for (json::iterator attr = json.begin(); attr != json.end(); ++attr) {
		if (attr.key() == "__pack" || attr.key() == "__id")
			continue;

		pack->AddAttribute(new PackageAttribute(attr.value().get<std::string>(), attr.key()));
	}

	/*------------------*/

	return pack;
}
