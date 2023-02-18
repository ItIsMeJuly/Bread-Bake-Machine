#ifndef MDISPLAY_H
#define MDISPLAY_H

#include "IDisplay.h"

#include <gmock/gmock.h>

class MDisplay: public IDisplay
{
public:
    MOCK_METHOD1(SetCurrentTask, void(Tasks));
    MOCK_METHOD1(SetMenu, void(int));
    MOCK_METHOD2(SetTime, void(int, int));
    MOCK_METHOD0(DisplayOff, void());
};

#endif
