#include "include.h"

StaticConsole Console::static_attributes;

void Console::Info(std::string message)
{
	std::cout << "[   ] ";
	std::cout << message << std::endl;
}

void Console::Pending(std::string message)
{
	std::cout << "[...] " << message << "\r";
}

void Console::OK(std::string message)
{
	SetConsoleTextAttribute(static_attributes.hConsole, FOREGROUND_GREEN);
	std::cout << "[OK ] ";
	SetConsoleTextAttribute(static_attributes.hConsole, static_attributes.hCDefault.wAttributes);

	std::cout << message << std::endl;
}

void Console::Warn(std::string warning)
{
	SetConsoleTextAttribute(static_attributes.hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	std::cout << "[WRN] ";
	SetConsoleTextAttribute(static_attributes.hConsole, static_attributes.hCDefault.wAttributes);

	std::cout << warning << std::endl;
}

void Console::Error(std::string error)
{
	SetConsoleTextAttribute(static_attributes.hConsole, FOREGROUND_RED);
	std::cout << "[ERROR] ";
	SetConsoleTextAttribute(static_attributes.hConsole, static_attributes.hCDefault.wAttributes);

	std::cout << error << std::endl;
}
