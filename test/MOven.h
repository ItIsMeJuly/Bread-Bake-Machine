#ifndef MOVEN_H
#define MOVEN_H

#include "IOven.h"

#include <gmock/gmock.h>

class MOven: public IOven
{
public:
    MOCK_METHOD1(StartRise, void(int));
    MOCK_METHOD1(StartBake, void(int));
    MOCK_CONST_METHOD0(IsOn, bool());
    MOCK_CONST_METHOD0(GetTemperature, int());
    MOCK_METHOD0(Cancel, void());
};

#endif
