#pragma once
class DecoderTemplate
{
	std::string content;
	std::string global_context;
	std::regex placeholder_regex;

public:
	const DecoderTemplate& operator<<(const std::string input);

	DecoderTemplate(nlohmann::json& conf);
	~DecoderTemplate();

	void Save(std::ofstream& file_out);
};

