#pragma once
class IncludeFile
{
	std::string content;
	std::string global_context;
	std::regex placeholder_regex;

	IncludeFile();

public:
	const IncludeFile& operator<<(const std::string input);

	IncludeFile(nlohmann::json& conf);
	~IncludeFile();

	void Save(std::ofstream& file_out);
};

