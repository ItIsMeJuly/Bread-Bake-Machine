#ifndef KNEADMOTOR_H
#define KNEADMOTOR_H

#include "IKneadMotor.h"
#include "Log.h"

class KneadMotor: public IKneadMotor
{
public:
    KneadMotor(Log& log);

    KneadMotor(const KneadMotor&) = delete;
    KneadMotor& operator=(const KneadMotor&) = delete;

    void TurnLeft();
    void TurnRight();
    void Stop();

private:
    Log& log;
};

#endif
