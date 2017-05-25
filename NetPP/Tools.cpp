#include "include.h"

namespace tools
{
	std::string GetExecutingPath()
	{
#if _WIN32
		char pBuf[MAX_PATH];
		int bytes = GetModuleFileName(NULL, pBuf, MAX_PATH);
		std::string apppath(pBuf);
#else
		char szTmp[32];
		sprintf(szTmp, "/proc/%d/exe", getpid());
		int bytes = MIN(readlink(szTmp, pBuf, len), len - 1);
		if (bytes >= 0)
			pBuf[bytes] = '\0';
		std::string apppath(pBuf);
#endif

		return apppath;
	}
}