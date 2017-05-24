#pragma once
class PackageAttribute
{
	std::string type;
	std::string name;

public:
	PackageAttribute(std::string _type, std::string _name);
	~PackageAttribute();

	std::string GetType() { return type; }
	std::string GetName() { return name; }
};

