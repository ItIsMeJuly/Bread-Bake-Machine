#ifndef DISPLAY_H
#define DISPLAY_H

#include "IDisplay.h"
#include "Log.h"


class Display: public IDisplay
{
public:
    Display(Log& log);

    Display(const Display& other) = delete;
    Display& operator=(const Display&) = delete;

    void SetCurrentTask(Tasks task);
    void SetMenu(int number);
    void SetTime(int hour, int min);
    void DisplayOff();

private:
    Log& log;
};

#endif
