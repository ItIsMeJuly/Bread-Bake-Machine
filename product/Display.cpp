#include "Display.h"

static const char* TaskText[] = { "NO TASK", "WAITING", "KNEADING",
                                  "RISING",  "BAKING",  "DONE" };
static const char* MenuText[] = { "Bread", "Bread +", "Bread Quick", "Dough",
                                  "Bake Only" };

Display::Display(Log& log)
    : log(log)
{
}

void Display::SetCurrentTask(Tasks task)
{
    log.Debug(">> %s: %s", __FUNCTION__, TaskText[task]);
}

void Display::SetMenu(int number)
{
    log.Debug(">> %s: %s", __FUNCTION__, MenuText[number]);
}

void Display::SetTime(int hour, int min)
{
    log.Debug(">> %s: %d:%d", __FUNCTION__, hour, min);
}

void Display::DisplayOff()
{
    log.Debug(">> %s", __FUNCTION__);
}
