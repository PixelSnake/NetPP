#include "include.h"

using json = nlohmann::json;

bool TreatParams(int argc, char * argv[]);
void PrintUsage();

bool TreatParams(int argc, char * argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		auto param = std::string(argv[i]);

		if (param == "-i")
			global::p_in = std::string(argv[++i]);
		else if (param == "-o")
			global::p_out = std::string(argv[++i]);
	}

	if (global::p_in.empty() || global::p_out.empty())
	{
		std::cout << "FATAL: Both in and out path have to be specified with -i and -o" << std::endl << std::endl;
		PrintUsage();
		return false;
	}

	return true;
}

void PrintUsage()
{
	using namespace std;

	cout << "NetPP v" << VERSION << " by " << AUTHOR << endl;
}

int main(int argc, char * argv[])
{
	if (!TreatParams(argc, argv))
		return 1;
}