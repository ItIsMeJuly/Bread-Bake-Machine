#ifndef STARTBUTTONLED_H
#define STARTBUTTONLED_H

#include "IStartButtonLed.h"
#include "Log.h"

class StartButtonLed: public IStartButtonLed
{
public:
    StartButtonLed(Log& log);

    StartButtonLed(const StartButtonLed&) = delete;
    StartButtonLed& operator=(const StartButtonLed&) = delete;

    void LedOn();
    void LedOff();

private:
    Log& log;
};

#endif
