#pragma once
class Package
{
	static int id_counter;

	int id;
	std::string classname;
	std::vector<PackageAttribute *> attributes;

public:
	Package(std::string _classname) : Package(_classname, id_counter++) {}
	Package(std::string _classname, int _id);
	~Package();

	std::string GetName() { return classname; }
	void AddAttribute(PackageAttribute * attr);

	void Compile(std::ostream& file_out, int language);
	std::string GenerateCodeCPP();
};

