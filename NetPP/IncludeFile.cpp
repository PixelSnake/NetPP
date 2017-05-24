#include "include.h"



IncludeFile::IncludeFile(std::string _filepath)
{
	filepath = _filepath;
}


IncludeFile::~IncludeFile()
{
}

void IncludeFile::AddInclude(std::string filepath)
{
	filenames.push_back(filepath);
}

void IncludeFile::Save()
{
	std::ofstream out(filepath, std::ios::out);

	out << "#pragma once\n\n";

	HRSRC hRes = FindResource(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_TEXT1), _T("TEXT"));
	DWORD dwSize = SizeofResource(GetModuleHandle(NULL), hRes);
	HGLOBAL hGlob = LoadResource(GetModuleHandle(NULL), hRes);
	const char * pData = reinterpret_cast<const char *>(::LockResource(hGlob));
	auto content = std::string(pData);

	out << content << "\n\n";

	for (auto file : filenames)
		out << "#include \"" << file << "\"\n";
}
