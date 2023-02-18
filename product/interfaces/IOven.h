#ifndef IOVEN_H
#define IOVEN_H

class IOven
{
public:
    virtual ~IOven() {};

    virtual void StartRise(int timeInMinutes) = 0;
    virtual void StartBake(int timeInMinutes) = 0;
    virtual bool IsOn() const = 0;
    virtual int GetTemperature() const = 0;
    virtual void Cancel() = 0;
};

#endif
