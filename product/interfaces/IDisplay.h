#ifndef IDISPLAY_H
#define IDISPLAY_H

#include "Tasks.h"

class IDisplay
{
public:
    virtual ~IDisplay() {};

    virtual void SetCurrentTask(Tasks task) = 0;
    virtual void SetMenu(int number) = 0;
    virtual void SetTime(int hour, int min) = 0;
    virtual void DisplayOff() = 0;
};

#endif
