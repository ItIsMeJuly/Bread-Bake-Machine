#ifndef MTIMERTIMEOUT_H
#define MTIMERTIMEOUT_H

#include "ITimerTimeout.h"

#include <gmock/gmock.h>

class MTimerTimeout: public ITimerTimeout
{
public:
    MOCK_METHOD0(TimerTimeout, void());
};

#endif
