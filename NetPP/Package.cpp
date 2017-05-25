#include "include.h"

int Package::id_counter = 0;


Package::Package(std::string _classname, int _id)
{
	id = _id;
	classname = _classname;
}

Package::~Package()
{
}

std::map<std::string, std::string> Package::CreatePlaceholderMap()
{
	std::map<std::string, std::string> map;

	map["CLASSNAME"] = classname;

	std::string private_attributes;
	private_attributes += "static const int _NPP_PACKTYPE = " + std::to_string(id) + ";\n";
	for (auto attr : attributes)
		private_attributes += attr->GetType() + " " + attr->GetName() + ";\n";
	map["PRIVATE_ATTRIBUTES"] = private_attributes;

	std::string constr_params;
	int counter = 0;
	for (auto attr : attributes)
		constr_params += (counter++ > 0 ? ", " : "") + attr->GetType() + " " + attr->GetName();
	map["CONSTR_PARAMS"] = constr_params;

	std::string constr_assign;
	for (auto attr : attributes)
		constr_assign += "this->" + attr->GetName() + " = " + attr->GetName() + ";\n";
	map["CONSTR_ASSIGN"] = constr_assign;

	map["ALGO_DECODE"] = CreateDecodingAlgorithm();
	map["ALGO_SEND"] = CreateSendingAlgorithm();

	return map;
}

std::string Package::CreateDecodingAlgorithm()
{
	std::string code;

	code += "auto pack = new " + classname + "();\n\n";
	code += "int offset = 0;\n\n";

	for (auto attr : attributes)
	{
		if (attr->GetType() == "std::string")
		{
			code += "pack->" + attr->GetName() + " = std::string(data + offset);\n";
			code += "offset += pack->" + attr->GetName() + ".length();\n";
			code += "\n";
		}
		else
		{
			code += "memcpy(&pack->" + attr->GetName() + ", data + offset, sizeof(" + attr->GetType() + "));\n";
			code += "offset += sizeof(" + attr->GetName() + ");\n";
			code += "\n";
		}
	}

	code += "return pack;\n";

	return code;
}

std::string Package::CreateSendingAlgorithm()
{
	std::string code;

	code += "int size = 0;\n";

	for (auto attr : attributes)
	{
		if (attr->GetType() == "std::string")
			code += "size += " + attr->GetName() + ".length();\n";
		else
			code += "size += sizeof(" + attr->GetType() + ");\n";
	}

	code += "\n";
	code += "char * data = calloc(size, 1);\n";
	code += "int offset = 0;\n";
	code += "\n";

	for (auto attr : attributes)
	{
		if (attr->GetType() == "std::string")
		{
			code += "memcpy(data + offset, " + attr->GetName() + ".c_str(), " + attr->GetName() + ".length());\n";
			code += "offset += " + attr->GetName() + ".length()\n";
			code += "\n";
		}
		else
		{
			code += "memcpy(data + offset, &" + attr->GetName() + ", sizeof(" + attr->GetName() + "));\n";
			code += "sizeof(" + attr->GetType() + ");\n";
			code += "\n";
		}
	}
	code += "send(sock, data, size, 0);\n";

	return code;
}

void Package::AddAttribute(PackageAttribute * attr)
{
	attributes.push_back(attr);
}

std::string Package::Compile(json& conf)
{
	PackageTemplate temp(conf);
	return temp.Replace(CreatePlaceholderMap());
}
