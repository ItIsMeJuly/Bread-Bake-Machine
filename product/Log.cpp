#include "Log.h"

#include <cstdio>

const bool DebugEnabled = true;
const bool TraceEnabled = true;


void Log::Debug(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    Write(DebugEnabled, fmt, args);
    va_end(args);
}

void Log::Trace(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    Write(TraceEnabled, fmt, args);
    va_end(args);
}

void Log::Write(bool enabled, const char* fmt, va_list ap)
{
    if (enabled)
    {
        const size_t MaxLength = 1000;
        char message[MaxLength];

        vsnprintf(message, MaxLength, fmt, ap);
        printf("%s\n", message);
    }
}
