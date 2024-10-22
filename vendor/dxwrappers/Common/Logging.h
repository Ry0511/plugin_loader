#pragma once

#include <fstream>
#include <stdarg.h>

class Log
{
public:
	Log() {}
	~Log()
	{
        // NOTE: Modified by plugin_loader; -Ry (2024/10/22)
	}

	template <typename T>
	Log& operator<<(const T& t)
	{
        // NOTE: Modified by plugin_loader; -Ry (2024/10/22)
        return *this;
	}
};

static std::ostream& operator<<(std::ostream& os, const wchar_t* wchr)
{
    // NOTE: Modified by plugin_loader; -Ry (2024/10/22)
    return os;
}

static void logf(char * fmt, ...)
{
    // NOTE: Modified by plugin_loader; -Ry (2024/10/22)
}

static void logf(wchar_t * fmt, ...)
{
    // NOTE: Modified by plugin_loader; -Ry (2024/10/22)
}
