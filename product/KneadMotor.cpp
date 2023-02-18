#include "KneadMotor.h"

KneadMotor::KneadMotor(Log& log)
    : log(log)
{
}

void KneadMotor::TurnLeft()
{
    log.Debug("KneadMotor is now TURNING LEFT");
}
void KneadMotor::TurnRight()
{
    log.Debug("KneadMotor is now TURNING RIGHT");
}
void KneadMotor::Stop()
{
    log.Debug("KneadMotor is now STOPPED");
}
