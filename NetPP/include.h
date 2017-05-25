#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <tchar.h>
#include <regex>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "lib\json.hpp"

#include "defines.h"
#include "global.h"
#include "Tools.h"
#include "Console.h"

#include "DecoderTemplate.h"
#include "PackageTemplate.h"
#include "IncludeFile.h"
#include "PackageAttribute.h"
#include "Package.h"
#include "JSONProcessor.h"