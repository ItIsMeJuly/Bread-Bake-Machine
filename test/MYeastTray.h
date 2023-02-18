#ifndef MYEASTTRAY_H
#define MYEASTTRAY_H

#include "IYeastTray.h"

#include <gmock/gmock.h>

class MYeastTray: public IYeastTray
{
public:
    MOCK_METHOD1(Drop, void(uint64_t));
    MOCK_METHOD0(Cancel, void());
};

#endif
