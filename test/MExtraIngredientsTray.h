#ifndef MEXTRAINGREDIENTSTRAY_H
#define MEXTRAINGREDIENTSTRAY_H

#include "IExtraIngredientsTray.h"

#include <gmock/gmock.h>

class MExtraIngredientsTray: public IExtraIngredientsTray
{
public:
    MOCK_METHOD1(Drop, void(uint64_t));
    MOCK_METHOD0(Cancel, void());
};

#endif
