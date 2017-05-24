#pragma once

using json = nlohmann::json;

class JSONProcessor
{
	json json;

public:
	JSONProcessor(std::string filepath);
	~JSONProcessor();

	void Compile(std::ostream& file_out);
};