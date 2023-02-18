#ifndef OVEN_H
#define OVEN_H

#include "IOven.h"
#include "IOvenSimulator.h"
#include "ITimer.h"
#include "ITimerTimeout.h"
#include "Log.h"

class Oven: public IOven, public ITimerTimeout, public IOvenSimulator
{
public:
    Oven(Log& log);

    Oven(const Oven&) = delete;
    Oven& operator=(const Oven&) = delete;

    void AddTimer(ITimer& timer);

    // IOven
    void StartRise(int timeInMinutes);
    void StartBake(int timeInMinutes);
    bool IsOn() const;
    int GetTemperature() const;
    void Cancel();

    // ITimerTimeout
    void TimerTimeout();

    // IOvenSimulator
    void SetTemperature(int temp);

private:
    ITimer* timer;
    Log& log;
    bool isOn;
    int currTemp;

    void SwitchOn(int timeInMinutes);
};

#endif
