#include "include.h"

bool TreatParams(int argc, char * argv[]);
void PrintUsage();

bool TreatParams(int argc, char * argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		auto param = std::string(argv[i]);

		if (param == "-i" && argc >= i + 1)
			global::p_in = std::string(argv[++i]);
		else if (param == "-o" && argc >= i + 1)
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

	
}

int main(int argc, char * argv[])
{
	std::cout << "NetPP v" << VERSION << " by " << AUTHOR << std::endl;

	if (!TreatParams(argc, argv))
		return 1;

	std::cout << "Input path: " << global::p_in.c_str() << std::endl;
	std::cout << "Output path: " << global::p_out.c_str() << std::endl;

	std::cout << global::p_in + "/handshake.json" << std::endl;

	JSONProcessor proc(global::p_in + "/handshake.json");
}