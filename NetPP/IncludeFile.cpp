#include "include.h"



const IncludeFile & IncludeFile::operator<<(const std::string input)
{
	content = content + input;
	return *this;
}

IncludeFile::IncludeFile()
{

}

IncludeFile::IncludeFile(json& conf)
{
	std::string contextpath;
	if (conf["global_context"] != nullptr)
		contextpath = conf["global_context"].get<std::string>();
	else
		throw std::string("Package template path not specified in config");

	contextpath = conf["__relative_path"].get<std::string>() + "\\" + contextpath;
	std::ifstream context(contextpath, std::ios::in);

	if (!context.good())
		throw std::string("File '" + contextpath + "' not found");

	global_context = std::string((std::istreambuf_iterator<char>(context)), std::istreambuf_iterator<char>());

	std::string ph_rx;
	if (conf["placeholder"] != nullptr)
		ph_rx = conf["placeholder"].get<std::string>();
	else
		throw std::string("Placeholder regular expression not specified in config");

	placeholder_regex = std::regex(ph_rx);
}


IncludeFile::~IncludeFile()
{
}

void IncludeFile::Save(std::ofstream& file_out)
{
	bool package_defs_inserted = false;
	std::smatch match;
	std::string result = global_context;

	while (std::regex_search(result, match, placeholder_regex))
	{
		if (match[1] == "PACKAGE_DEFS")
		{
			if (package_defs_inserted)
				Console::Warn("Placeholder PACKAGE_DEFS specified more than once");

			result = result.replace(match.position(), match.length(), content);
			package_defs_inserted = true;
		}
		else
			Console::Warn(std::string("Placeholder ") + match[1].str() + " not allowed in global context. Ignored");
	}
	
	if (!package_defs_inserted)
	{
		Console::Warn("No PACKAGE_DEFS placeholder specified in global context");
	}

	file_out << result;
}
