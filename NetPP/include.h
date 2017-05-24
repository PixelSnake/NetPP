#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <tchar.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "lib\json.hpp"
#include "resource1.h"

#include "defines.h"
#include "global.h"

#include "Console.h"
#include "IncludeFile.h"
#include "PackageAttribute.h"
#include "Package.h"
#include "JSONProcessor.h"