#ifndef IOVENSIMULATOR_H
#define IOVENSIMULATOR_H

class IOvenSimulator
{
public:
    virtual ~IOvenSimulator() {};

    virtual void SetTemperature(int temp) = 0;
};

#endif
