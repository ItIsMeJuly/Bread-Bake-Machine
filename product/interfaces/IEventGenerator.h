#ifndef IEVENTGENERATOR_H
#define IEVENTGENERATOR_H

#include "Events.h"

#include <optional>

class IEventGenerator
{
public:
    virtual ~IEventGenerator() {};

    virtual std::optional<Events> GetEvent() = 0;
};

#endif
