#pragma once
class IncludeFile
{
	std::string filepath;
	std::vector<std::string> filenames;

public:
	IncludeFile(std::string _filepath);
	~IncludeFile();

	void AddInclude(std::string filepath);
	void Save();
};

