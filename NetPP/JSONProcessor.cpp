#include "include.h"



JSONProcessor::JSONProcessor(std::string filepath)
{
	std::ifstream i(filepath, std::ios::in);
	i >> json;

	std::cout << json["__pack"];
}


JSONProcessor::~JSONProcessor()
{
}

void JSONProcessor::Compile(std::ostream& file_out)
{
	file_out << "Lappen";
}
