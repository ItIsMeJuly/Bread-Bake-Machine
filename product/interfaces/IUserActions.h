#ifndef IUSERACTIONS_H
#define IUSERACTIONS_H

class IUserActions
{
public:
    virtual ~IUserActions() {};

    virtual void MenuPressed() = 0;
    virtual void MenuLongPressed() = 0;
    virtual void TimerUpPressed() = 0;
    virtual void TimerDownPressed() = 0;
    virtual void StartPressed() = 0;
};

#endif
