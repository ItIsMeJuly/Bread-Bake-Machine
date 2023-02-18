#ifndef MSTARTBUTTONLED_H
#define MSTARTBUTTONLED_H

#include "IStartButtonLed.h"

#include <gmock/gmock.h>

class MStartButtonLed: public IStartButtonLed
{
public:
    MOCK_METHOD0(LedOn, void());
    MOCK_METHOD0(LedOff, void());
};

#endif
