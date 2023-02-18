#ifndef ITIMER_H
#define ITIMER_H

#include <stdint.h>

class ITimer
{
public:
    virtual ~ITimer() {};

    virtual void Set(uint64_t time) = 0;
    virtual void Cancel() = 0;
};

#endif
