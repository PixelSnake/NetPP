#pragma once

using json = nlohmann::json;

class JSONProcessor
{
public:
	static Package * ProcessPackage(std::string filepath);
};