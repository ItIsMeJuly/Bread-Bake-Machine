#ifndef EXTRAINGREDIENTSTRAY_H
#define EXTRAINGREDIENTSTRAY_H

#include "IExtraIngredientsTray.h"
#include "Log.h"


class ExtraIngredientsTray: public IExtraIngredientsTray
{
public:
    ExtraIngredientsTray(Log& log);
    ExtraIngredientsTray(const ExtraIngredientsTray&) = delete;
    ExtraIngredientsTray& operator=(const ExtraIngredientsTray&) = delete;

    void Drop(uint64_t time);
    void Cancel();

private:
    Log& log;
};

#endif
