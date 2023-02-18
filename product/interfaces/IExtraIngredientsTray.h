#ifndef IEXTRAINGREDIENTSTRAY_H
#define IEXTRAINGREDIENTSTRAY_H

#include <stdint.h>

class IExtraIngredientsTray
{
public:
    virtual ~IExtraIngredientsTray() {};

    virtual void Drop(uint64_t time) = 0;
    virtual void Cancel() = 0;
};

#endif
