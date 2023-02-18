#ifndef MUSERACTIONS_H
#define MUSERACTIONS_H

#include "IUserActions.h"

#include <gmock/gmock.h>

class MUserActions: public IUserActions
{
public:
    MOCK_METHOD0(MenuPressed, void());
    MOCK_METHOD0(MenuLongPressed, void());
    MOCK_METHOD0(TimerUpPressed, void());
    MOCK_METHOD0(TimerDownPressed, void());
    MOCK_METHOD0(StartPressed, void());
};

#endif
