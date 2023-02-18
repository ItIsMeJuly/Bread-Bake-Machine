#include "EventGenerator.h"

static const char* EventStrings[] = {
    "NO_EVENT_OCCURRED",
    "MENU_BUTTON_PRESSED",
    "MENU_BUTTON_LONG_PRESSED",
    "TIMER_UP_BUTTON_PRESSED",
    "TIMER_DOWN_BUTTON_PRESSED",
    "START_BUTTON_PRESSED",
    "OVEN_DONE",
    "TIMER_TIMEOUT"
};

EventGenerator::EventGenerator(IOven& oven, Log& log)
    : oven(oven)
    , prevOvenOn(false)
    , log(log)
{
}

std::optional<Events> EventGenerator::GetEvent()
{
    std::optional<Events> result = std::nullopt;

    HandlePollEvents();

    {
        std::lock_guard<std::mutex> guard(eventGuard);
        if (events.size() > 0)
        {
            result = events[0];
            events.erase(events.begin());
        }
    }

    if (result != std::nullopt)
    {
        log.Debug("== GetEvent returns: %s", EventStrings[*result]);
    }
    return result;
}

void EventGenerator::TimerTimeout()
{
    PushEvent(Events::TIMER_TIMEOUT);
}
void EventGenerator::MenuPressed()
{
    PushEvent(Events::MENU_BUTTON_PRESSED);
}
void EventGenerator::MenuLongPressed()
{
    PushEvent(Events::MENU_BUTTON_LONG_PRESSED);
}
void EventGenerator::TimerUpPressed()
{
    PushEvent(Events::TIMER_UP_BUTTON_PRESSED);
}
void EventGenerator::TimerDownPressed()
{
    PushEvent(Events::TIMER_DOWN_BUTTON_PRESSED);
}
void EventGenerator::StartPressed()
{
    PushEvent(Events::START_BUTTON_PRESSED);
}


void EventGenerator::HandlePollEvents()
{
    if (oven.IsOn())
    {
        prevOvenOn = true;
    }
    else
    {
        if (prevOvenOn)
        {
            prevOvenOn = false;
            PushEvent(Events::OVEN_DONE);
        }
    }
}

void EventGenerator::PushEvent(Events event)
{
    {
        std::lock_guard<std::mutex> guard(eventGuard);
        events.push_back(event);
    }
    log.Debug("%s event occurred", EventStrings[event]);
}
