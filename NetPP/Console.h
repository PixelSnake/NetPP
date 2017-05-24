#pragma once

class StaticConsole
{
public:
	CONSOLE_SCREEN_BUFFER_INFO hCDefault;
	HANDLE hConsole;

	StaticConsole()
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &hCDefault);
	}

	~StaticConsole()
	{
		SetConsoleTextAttribute(hConsole, hCDefault.wAttributes);
	}
};

class Console
{
	static StaticConsole static_attributes;

public:
	static void Info(std::string message);
	static void Pending(std::string message);
	static void OK(std::string message);
	static void Warn(std::string warning);
	static void Error(std::string error);
};

