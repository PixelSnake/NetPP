#include "include.h"



PackageTemplate::PackageTemplate(json& conf)
{
	std::string temppath;
	if (conf["pack_template"] != nullptr)
		temppath = conf["pack_template"].get<std::string>();
	else
		throw "Package template path not specified in config";

	temppath = conf["__relative_path"].get<std::string>() + "\\" + temppath;
	std::cout << temppath << std::endl;
	std::ifstream temp(temppath, std::ios::in);

	if (!temp.good())
		throw std::string("Template file given in config does not exist");

	template_content = std::string((std::istreambuf_iterator<char>(temp)), std::istreambuf_iterator<char>());

	std::string ph_rx;
	if (conf["placeholder"] != nullptr)
		ph_rx = conf["placeholder"].get<std::string>();
	else
		throw "Placeholder regular expression not specified in config";

	placeholder_regex = std::regex(ph_rx);
}


PackageTemplate::~PackageTemplate()
{
}

std::string PackageTemplate::Replace(std::map<std::string, std::string>& placeholders)
{
	std::smatch match;

	while (std::regex_search(template_content, match, placeholder_regex))
	{
		template_content = template_content.replace(match.position(), match.length(), placeholders[match[1]]);
	}

	return template_content;
}
