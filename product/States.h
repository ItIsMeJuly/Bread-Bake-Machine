#ifndef STATES_H
#define STATES_H

enum States
{
    STANDBY,
    SELECT_PROGRAM,
    START_PROGRAM,
};

enum Kneading
{
    WAIT_YEAST,
    ADD_YEAST,
    WAIT_INGREDIENT,
    POUR_INGREDIENT,
    START_KNEADING,
};

#endif
