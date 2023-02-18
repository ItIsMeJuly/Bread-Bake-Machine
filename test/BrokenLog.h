#ifndef BROKENLOG_H
#define BROKENLOG_H

#include "Log.h"
#include <stdarg.h>

class BrokenLog: public Log
{
public:
    void Debug(const char*, ...) {};
    void Trace(const char*, ...) {};
};

#endif
