#ifndef IKNEADMOTOR_H
#define IKNEADMOTOR_H

class IKneadMotor
{
public:
    virtual ~IKneadMotor() {};

    virtual void TurnLeft() = 0;
    virtual void TurnRight() = 0;
    virtual void Stop() = 0;
};

#endif
