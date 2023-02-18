#ifndef IYEASTTRAY_H
#define IYEASTTRAY_H

#include <stdint.h>

class IYeastTray
{
public:
    virtual ~IYeastTray() {};

    virtual void Drop(uint64_t time) = 0;
    virtual void Cancel() = 0;
};

#endif
