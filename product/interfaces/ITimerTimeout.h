#ifndef ITIMERTIMEOUT_H
#define ITIMERTIMEOUT_H

class ITimerTimeout
{
public:
    virtual ~ITimerTimeout() {};

    virtual void TimerTimeout() = 0;
};

#endif
