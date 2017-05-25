#pragma once
class PackageTemplate
{
	std::string template_content;
	std::regex placeholder_regex;

public:
	PackageTemplate(nlohmann::json& conf);
	~PackageTemplate();

	std::string Replace(std::map<std::string, std::string>& placeholders);
};

