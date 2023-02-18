#include "Timer.h"

#include <stdexcept>

// To prevent endless waiting during testing, your timer can make use of the
// GetSimulatedTime method, which will divide waiting time by factor
// TimeDivider and will limit the maximum waiting time to MaxTimeInMiliseconds.
// To get reasonably normal timing, set TimeDivider to 1 and
// MaxTimeInMiliseconds to std::numeric_limits<uint64_t>::max() (or another
// really big number).
const uint64_t TimeDivider = 50;
const uint64_t MaxTimeInMiliseconds = 10000;

Timer::Timer(ITimerTimeout& timerTimeout, Log& log)
    : timerTimeout(timerTimeout)
    , log(log)
    , timerRunning(false)
    , timerThread(nullptr)
{
}

Timer::~Timer()
{
    Cleanup();
}

void Timer::Set(uint64_t time)
{
    if (timerRunning)
    {
        throw std::logic_error("timer is already running");
    }
    Cleanup();

    uint64_t nrTicks = GetSimulatedTime(time);
    log.Debug("timer set to: %lu ms (%lu min  ==> simulated time: %lu ms)",
              time, SecToMSec(time), nrTicks);

    timerRunning = true;
    timerThread = new std::thread(&Timer::Run, this, nrTicks);
}

void Timer::Cancel()
{
    log.Trace(">> %s::%s", __FILE__, __FUNCTION__);
    timerRunning = false;
}

void Timer::Run(uint64_t nrTicks)
{
    for (uint64_t i = 0; i < nrTicks && timerRunning; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    if (timerRunning)
    {
        log.Debug("Timer timout occurred");
        timerTimeout.TimerTimeout();
        timerRunning = false;
    }
}


void Timer::Cleanup()
{
    if (timerThread != nullptr)
    {
        timerRunning = false;
        timerThread->join();

        delete timerThread;
        timerThread = nullptr;
    }
}

uint64_t Timer::GetSimulatedTime(uint64_t time)
{
    uint64_t simulatedTime = time / TimeDivider;
    if (simulatedTime > MaxTimeInMiliseconds)
    {
        simulatedTime = MaxTimeInMiliseconds;
    }
    return simulatedTime;
}

uint64_t Timer::SecToMSec(uint64_t timeInSec)
{
    return timeInSec / 60000;
}
