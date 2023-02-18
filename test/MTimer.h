#ifndef MTIMER_H
#define MTIMER_H

#include "ITimer.h"

#include <gmock/gmock.h>

class MTimer: public ITimer
{
public:
    MOCK_METHOD1(Set, void(uint64_t));
    MOCK_METHOD0(Cancel, void());
};

#endif
