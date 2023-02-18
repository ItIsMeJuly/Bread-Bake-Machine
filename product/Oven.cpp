#include "Oven.h"
#include "TimeConstants.h"

#include <stdexcept>

Oven::Oven(Log& log)
    : timer(nullptr)
    , log(log)
    , isOn(false)
    , currTemp(0)
{
}

void Oven::AddTimer(ITimer& timer)
{
    if (this->timer != nullptr)
    {
        throw std::logic_error("timer was already added");
    }
    this->timer = &timer;
}

void Oven::StartRise(int timeInMinutes)
{
    log.Trace(">> %s: %d minutes", __FUNCTION__, timeInMinutes);
    SwitchOn(timeInMinutes);
}

void Oven::StartBake(int timeInMinutes)
{
    log.Trace(">> %s: %d minutes", __FUNCTION__, timeInMinutes);
    SwitchOn(timeInMinutes);
}

bool Oven::IsOn() const
{
    // log.Trace(">> %s: %s", __FUNCTION__, isOn ? "true" : "false");
    return isOn;
}

int Oven::GetTemperature() const
{
    log.Trace(">> %s: %d", __FUNCTION__, currTemp);
    return currTemp;
}

void Oven::Cancel()
{
    log.Trace(">> %s::%s", __FILE__, __FUNCTION__);

    if (this->timer == nullptr)
    {
        throw std::logic_error("oven cannot be used without timer");
    }

    isOn = false;
    timer->Cancel();
}

void Oven::TimerTimeout()
{
    log.Trace(">> %s::%s", __FILE__, __FUNCTION__);
    isOn = false;
}


// for simulation
void Oven::SetTemperature(int temp)
{
    currTemp = temp;
    log.Debug(">> %s: %d degrees", __FUNCTION__, currTemp);
}

// private
void Oven::SwitchOn(int timeInMinutes)
{
    log.Trace(">> %s::%s", __FILE__, __FUNCTION__);
    if (this->timer == nullptr)
    {
        throw std::logic_error("oven cannot be switched on without timer");
    }

    timer->Set(timeInMinutes * MIN);
    isOn = true;
}
