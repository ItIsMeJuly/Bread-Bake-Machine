#ifndef EVENTGENERATOR_H
#define EVENTGENERATOR_H

#include "Events.h"
#include "IEventGenerator.h"
#include "IOven.h"
#include "ITimerTimeout.h"
#include "IUserActions.h"
#include "Log.h"

#include <mutex>
#include <vector>

class EventGenerator : public IEventGenerator,
                       public ITimerTimeout,
                       public IUserActions
{
public:
    EventGenerator(IOven& oven, Log& log);

    EventGenerator(const EventGenerator& other) = delete;
    EventGenerator& operator=(const EventGenerator&) = delete;

    // IEventGenerator
    std::optional<Events> GetEvent();

    // ITimerTimeout
    void TimerTimeout();

    // IUserActions
    // Dirty, I know but good enough for now (shouldn't be in
    // EventGenerator, but for simulation it's good enough)
    void MenuPressed();
    void MenuLongPressed();
    void TimerUpPressed();
    void TimerDownPressed();
    void StartPressed();

private:
    IOven& oven;
    std::vector<Events> events;
    std::mutex eventGuard;
    bool prevOvenOn;
    Log& log;

    void HandlePollEvents();
    void PushEvent(Events event);
};

#endif
