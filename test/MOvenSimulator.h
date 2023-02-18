#ifndef MOVENSIMULATOR_H
#define MOVENSIMULATOR_H

#include "IOvenSimulator.h"

#include <gmock/gmock.h>

class MOvenSimulator: public IOvenSimulator
{
public:
    MOCK_METHOD1(SetTemperature, void(int));
};

#endif
