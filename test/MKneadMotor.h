#ifndef MKNEADMOTOR_H
#define MKNEADMOTOR_H

#include "IKneadMotor.h"

#include <gmock/gmock.h>

class MKneadMotor: public IKneadMotor
{
public:
    MOCK_METHOD0(TurnLeft, void());
    MOCK_METHOD0(TurnRight, void());
    MOCK_METHOD0(Stop, void());
};

#endif
