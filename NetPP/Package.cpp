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

std::string Package::GenerateCodeCPP()
{
	std::string code;

	code += "#pragma once\n";

	/* class */
	code += "class " + classname + " : PackageFactory<" + classname + ", IPackage>, IPackage\n";
	code += "{\n";
	{
		code += "\tstatic const int _NPP_PACKTYPE = " + std::to_string(id) + ";\n\n";

		for (auto attr : attributes)
			code += "\t" + attr->GetType() + " " + attr->GetName() + ";\n";

		code += "\n";

		code += "\t" + classname + "() {}\n";

		code += "\n";
		code += "public:\n";


		/* constructor */
		code += "\t" + classname + "(";

		int counter = 0;
		for (auto attr : attributes)
			code += (counter++ > 0 ? ", " : "") + attr->GetType() + " " + attr->GetName();

		code += ")\n";

		code += "\t{\n";
		{
			for (auto attr : attributes)
				code += "\t\tthis->" + attr->GetName() + " = " + attr->GetName() + ";\n";
		}
		code += "\t}\n\n";

		code += "\t~" + classname + "() {}\n\n";

		/* decode function */
		code += "\tstatic " + classname + " * Decode(char * data)\n";
		code += "\t{\n";
		{
			code += "\t\tauto pack = new " + classname + "();\n\n";
			code += "\t\tint offset = 0;\n\n";

			for (auto attr : attributes)
			{
				if (attr->GetType() == "std::string")
				{
					code += "\t\tpack->" + attr->GetName() + " = std::string(data + offset);\n";
					code += "\t\toffset += pack->" + attr->GetName() + ".length();\n";
					code += "\n";
				}
				else
				{
					code += "\t\tmemcpy(&pack->" + attr->GetName() + ", data + offset, sizeof(" + attr->GetType() + "));\n";
					code += "\t\toffset += sizeof(" + attr->GetName() + ");\n";
					code += "\n";
				}
			}

			code += "\t\treturn pack;\n";
		}
		code += "\t}\n\n";


		code += "\tvoid Send(SOCKET sock)\n";
		code += "\t{\n";
		{
			code += "\t\tint size = 0;\n";

			for (auto attr : attributes)
			{
				if (attr->GetType() == "std::string")
					code += "\t\tsize += " + attr->GetName() + ".length();\n";
				else
					code += "\t\tsize += sizeof(" + attr->GetType() + ");\n";
			}

			code += "\n";
			code += "\t\tchar * data = calloc(size, 1);\n";
			code += "\t\tint offset = 0;\n";
			code += "\n";

			for (auto attr : attributes)
			{
				if (attr->GetType() == "std::string")
				{
					code += "\t\tmemcpy(data + offset, " + attr->GetName() + ".c_str(), " + attr->GetName() + ".length());\n";
					code += "\t\toffset += " + attr->GetName() + ".length()\n";
					code += "\n";
				}
				else
				{
					code += "\t\tmemcpy(data + offset, &" + attr->GetName() + ", sizeof(" + attr->GetName() + "));\n";
					code += "\t\tsizeof(" + attr->GetType() + ");\n";
					code += "\n";
				}
			}
			code += "\t\tsend(sock, data, size, 0);\n";
		}
		code += "\t}\n";
	}
	code += "}\n";

	return code;
}

void Package::AddAttribute(PackageAttribute * attr)
{
	attributes.push_back(attr);
}

void Package::Compile(std::ostream & file_out, int language)
{
	switch (language)
	{
	case LANG_CPP:
		file_out << GenerateCodeCPP();
	}
}
