#include "ExtraIngredientsTray.h"


ExtraIngredientsTray::ExtraIngredientsTray(Log& log)
    : log(log)
{
}

void ExtraIngredientsTray::Drop(uint64_t time)
{
    log.Debug("ExtraIngredientsTray: dropping extras in %lus", time / 1000);
}

void ExtraIngredientsTray::Cancel()
{
    log.Trace("ExtraIngredientsTray: dropping cancelled");
}
