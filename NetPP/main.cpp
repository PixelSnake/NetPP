#include "include.h"

bool TreatParams(int argc, char * argv[]);
void PrintUsage();

void LoadGlobals()
{
	std::ifstream cfg(".nppconf", std::ios::in);

	if (!cfg.good())
	{
		Console::Warn("No .nppconf found");
		return;
	}

	json j;
	cfg >> j;

	if (j["input"] != nullptr)
		global::p_in = j["input"].get<std::string>();

	if (j["output"] != nullptr)
		global::p_out = j["output"].get<std::string>();

	if (j["language"] != nullptr)
		global::language = j["language"].get<std::string>();
}

json LoadLanguageConfig(std::string lang)
{
	std::string apppath = tools::GetExecutingPath();
	std::string config_path = std::experimental::filesystem::path(apppath).remove_filename().string() + "/lang/" + lang + "/" + lang + ".nppconf";
	std::ifstream file(config_path, std::ios::in);

	if (!file.good())
		throw std::string("File '" + config_path + "' not found");

	json conf;
	file >> conf;

	std::string relpath = std::experimental::filesystem::path(config_path).remove_filename().string();
	conf["__relative_path"] = relpath;

	return conf;
}

bool TreatParams(int argc, char * argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		auto param = std::string(argv[i]);

		if (param == "-i" && argc >= i + 1)
			global::p_in = std::string(argv[++i]);
		else if (param == "-o" && argc >= i + 1)
			global::p_out = std::string(argv[++i]);
		else if (param == "-l" || param == "--lang" && argc >= i + 1)
			global::language = std::string(argv[++i]);
	}

	if (global::p_in.empty() || global::p_out.empty())
	{
		Console::Error("Both in and out path have to be specified with -i and -o");
		PrintUsage();
		return false;
	}

	if (global::language.empty())
	{
		Console::Error("Language not specified");
		PrintUsage();
		return false;
	}

	return true;
}

void PrintUsage()
{
	using namespace std;

	std::cout << std::endl;
	std::cout << "Usage: " << std::endl;

	Console::PrintWithAttributes("\t -l --lang\t", FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Specify output language, overrides config value" << std::endl;

	Console::PrintWithAttributes("\t -i\t", FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Input path, overrides config value" << std::endl;

	Console::PrintWithAttributes("\t -o\t", FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Output path, overrides config value" << std::endl;
}

int main(int argc, char * argv[])
{
	std::cout << "NetPP v" << VERSION << " by " << AUTHOR << std::endl;

	LoadGlobals();

	if (!TreatParams(argc, argv))
		return 1;

	std::cout << "Input path: \"" << global::p_in.c_str() << "\"" << std::endl;
	std::cout << "Output path: \"" << global::p_out.c_str() << "\"" << std::endl;
	std::cout << std::endl;

	try
	{
		auto config = LoadLanguageConfig(global::language);

		IncludeFile include(config);
		DecoderTemplate decoder(config);

		decoder << "switch (packtype)\n{\n";

		for (auto & p : std::experimental::filesystem::directory_iterator(global::p_in))
		{
			if (p.path().extension() != ".json")
				continue;

			std::cout << "-- " << p.path().string() << std::endl;

			auto package = JSONProcessor::ProcessPackage(p.path().string());
			include << package->Compile(config);

			decoder << std::string("case ") + std::to_string(package->GetId()) + ":\nreturn " + package->GetName() + "::Decode(data);\n\n";

			Console::OK("Transpiling " + p.path().string());
		}

		decoder << "}\n";

		std::ofstream include_out(global::p_out + "\\netpp.hpp", std::ios::out);
		include.Save(include_out);
		decoder.Save(include_out);
	}
	catch (std::string msg)
	{
		Console::Error(msg);
		return 1;
	}
}