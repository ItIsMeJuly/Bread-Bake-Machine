#ifndef TIMER_H
#define TIMER_H

#include "ITimer.h"
#include "ITimerTimeout.h"
#include "Log.h"

#include <thread>

class Timer: public ITimer
{
public:
    Timer(ITimerTimeout& timerTimeout, Log& log);
    ~Timer();

    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;

    // ITimer
    void Set(uint64_t time);
    void Cancel();

    void Run(uint64_t nrTicks);

private:
    ITimerTimeout& timerTimeout;
    Log& log;
    bool timerRunning;
    std::thread* timerThread;

    void Cleanup();
    uint64_t GetSimulatedTime(uint64_t time);
    uint64_t SecToMSec(uint64_t timeInSec);
};

#endif
