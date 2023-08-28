#include <iostream>
#include <Windows.h>
#include <direct.h>

#ifndef __LOG_FUNCTION__
#define __LOG_FUNCTION__

#define __FILENAME__ (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1) : __FILE__)

// Log Macro Function
#define LOG(...) Log(__FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)

void Log(const char *fileName, const char *functionName, int lineNumber, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    printf("[%s:%d (%s)] ", fileName, lineNumber, functionName);
    vprintf(format, args);
    printf("\n");

    va_end(args);
}

#endif // __LOG_FUNCTION__