#ifndef LOG_H
#define LOG_H

#include <stdarg.h>

class Log
{
public:
    Log() = default;
    Log(Log const&) = delete;
    Log& operator=(Log const&) = delete;

    virtual void Debug(const char* fmt, ...);
    virtual void Trace(const char* fmt, ...);

private:
    void Write(bool enabled, const char* fmt, va_list ap);
};

#endif
