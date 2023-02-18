#ifndef ISTARTBUTTONLED_H
#define ISTARTBUTTONLED_H

class IStartButtonLed
{
public:
    virtual ~IStartButtonLed() {};

    virtual void LedOn() = 0;
    virtual void LedOff() = 0;
};

#endif
