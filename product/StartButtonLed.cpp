#include "StartButtonLed.h"

StartButtonLed::StartButtonLed(Log& log)
    : log(log)
{
}

void StartButtonLed::LedOn()
{
    log.Trace(">> %s", __FUNCTION__);
}
void StartButtonLed::LedOff()
{
    log.Trace(">> %s", __FUNCTION__);
}
