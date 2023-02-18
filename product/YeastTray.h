#ifndef YEASTTRAY_H
#define YEASTTRAY_H

#include "IYeastTray.h"
#include "Log.h"

class YeastTray: public IYeastTray
{
public:
    YeastTray(Log& log);

    YeastTray(const YeastTray&) = delete;
    YeastTray& operator=(const YeastTray&) = delete;

    void Drop(uint64_t time);
    void Cancel();

private:
    Log& log;
};

#endif
