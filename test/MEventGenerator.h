#ifndef MEVENTGENERATOR_H
#define MEVENTGENERATOR_H

#include "IEventGenerator.h"

#include <gmock/gmock.h>

class MEventGenerator: public IEventGenerator
{
public:
    MOCK_METHOD0(GetEvent, std::optional<Events>());
};

#endif
