#pragma once
class Package
{
	static int id_counter;

	int id;
	std::string classname;
	std::vector<PackageAttribute *> attributes;

	std::map<std::string, std::string> CreatePlaceholderMap();
	std::string CreateDecodingAlgorithm();
	std::string CreateSendingAlgorithm();

public:
	Package(std::string _classname) : Package(_classname, id_counter++) {}
	Package(std::string _classname, int _id);
	~Package();

	int GetId() { return id; }
	std::string GetName() { return classname; }
	void AddAttribute(PackageAttribute * attr);

	std::string Compile(nlohmann::json& conf);
};

