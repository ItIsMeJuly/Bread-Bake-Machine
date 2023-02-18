#include "BreadBaker.h"
#include "BrokenLog.h"
#include "MDisplay.h"
#include "MEventGenerator.h"
#include "MExtraIngredientsTray.h"
#include "MKneadMotor.h"
#include "MOven.h"
#include "MStartButtonLed.h"
#include "MTimer.h"
#include "MYeastTray.h"
#include "TimeConstants.h"

using ::testing::Return;
using ::testing::_;

class StateTest: public ::testing::Test
{
protected:
    StateTest()
    {
        baker = new BreadBaker(
                    oven, timer, motor, yeast, extras,
                    display, startButton, event, log);
    }

    virtual ~StateTest()
    {
        delete baker;
        baker = nullptr;
    }

    MDisplay display;
    MEventGenerator event;
    MExtraIngredientsTray extras;
    MKneadMotor motor;
    MOven oven;
    MStartButtonLed startButton;
    MTimer timer;
    MYeastTray yeast;

    BrokenLog log;
    BreadBaker* baker;
};

TEST_F(StateTest, test_BrokenEmptyTest)
{
    EXPECT_CALL(display, SetCurrentTask(_)).Times(0); // please note: _ is a wildcard, it means: "any value for that parameter"
    EXPECT_CALL(display, SetMenu(_)).Times(0);
    EXPECT_CALL(display, SetTime(_, _)).Times(0);
    EXPECT_CALL(display, DisplayOff()).Times(0);

    EXPECT_CALL(event, GetEvent()).Times(0);

    EXPECT_CALL(extras, Drop(_)).Times(0);
    EXPECT_CALL(extras, Cancel()).Times(0);

    EXPECT_CALL(motor, TurnLeft()).Times(0);
    EXPECT_CALL(motor, TurnRight()).Times(0);
    EXPECT_CALL(motor, Stop()).Times(0);

    EXPECT_CALL(oven, StartRise(_)).Times(0);
    EXPECT_CALL(oven, StartBake(_)).Times(0);
    EXPECT_CALL(oven, IsOn()).Times(0);
    EXPECT_CALL(oven, GetTemperature()).Times(0);
    EXPECT_CALL(oven, Cancel()).Times(0);

    EXPECT_CALL(startButton, LedOn()).Times(0);
    EXPECT_CALL(startButton, LedOff()).Times(0);

    EXPECT_CALL(timer, Set(_)).Times(0);
    EXPECT_CALL(timer, Cancel()).Times(0);

    EXPECT_CALL(yeast, Drop(_)).Times(0);
    EXPECT_CALL(yeast, Cancel()).Times(0);

    EXPECT_EQ(1, 0); // a Google test project must have at least one EXPECT_... or ASSERT_..., else it won't compile
}


TEST_F(StateTest, test_idle_state0)
{
    States state = STANDBY;
    Events ev = MENU_BUTTON_PRESSED;

    EXPECT_CALL(oven, GetTemperature());

    baker->HandleStandby(ev, state);

    EXPECT_EQ(States::SELECT_PROGRAM, state);
}

TEST_F(StateTest, test_idle_state1)
{
    States state = STANDBY;
    Events ev = TIMER_TIMEOUT;

    EXPECT_CALL(timer, Set(_));

    baker->HandleStandby(ev, state);

    EXPECT_EQ(States::STANDBY, state);
}

TEST_F(StateTest, test_program_selection)
{
    Program operation; int program = 2; int totalTime = 0;

    baker->HandleSelectProgram(operation, program, totalTime);

    EXPECT_EQ(40, operation.waiting);
    EXPECT_EQ(15, operation.kneading);
    EXPECT_EQ(60, operation.rising);
    EXPECT_EQ(0, operation.baking);
}


TEST_F(StateTest, test_select_state0)
{
    Events ev = MENU_BUTTON_PRESSED; States state = SELECT_PROGRAM; int program = 2; int totalTime; Program operation;

    EXPECT_CALL(timer, Set(_));
    EXPECT_CALL(display, SetTime(_, _));
    EXPECT_CALL(display, SetMenu(_));
    EXPECT_CALL(timer, Cancel());

    baker->HandleSelect(ev, state, program, totalTime, operation);
    
    EXPECT_EQ(SELECT_PROGRAM, state);
}

TEST_F(StateTest, test_select_state1)
{
    Events ev = TIMER_DOWN_BUTTON_PRESSED; States state = SELECT_PROGRAM; int program = 2; int totalTime; Program operation;
    baker->delayTime = 20;

    EXPECT_CALL(display, SetMenu(_));
    EXPECT_CALL(display, SetTime(_, _));
    EXPECT_CALL(timer, Cancel());

    baker->HandleSelect(ev, state, program, totalTime, operation);
    
    EXPECT_EQ(10, baker->delayTime);
}


TEST_F(StateTest, test_select_state2)
{
    Events ev = TIMER_UP_BUTTON_PRESSED; States state = SELECT_PROGRAM; int program = 2; int totalTime; Program operation;
    baker->delayTime = 20;

    EXPECT_CALL(display, SetMenu(_));
    EXPECT_CALL(display, SetTime(_, _));
    EXPECT_CALL(timer, Cancel());

    baker->HandleSelect(ev, state, program, totalTime, operation);
    
    EXPECT_EQ(30, baker->delayTime);
}


TEST_F(StateTest, test_select_state3)
{
    Events ev = TIMER_DOWN_BUTTON_PRESSED; States state = SELECT_PROGRAM; int program = 4; int totalTime; Program operation;
    operation.baking = 40;
    baker->delayTime = 20;

    EXPECT_CALL(display, SetMenu(_));
    EXPECT_CALL(display, SetTime(_, _));
    EXPECT_CALL(timer, Cancel());

    baker->HandleSelect(ev, state, program, totalTime, operation);
    
    EXPECT_EQ(35, operation.baking);
}


TEST_F(StateTest, test_select_state4)
{
    Events ev = TIMER_UP_BUTTON_PRESSED; States state = SELECT_PROGRAM; int program = 4; int totalTime; Program operation;
    operation.baking = 40;
    baker->delayTime = 20;

    EXPECT_CALL(display, SetMenu(_));
    EXPECT_CALL(display, SetTime(_, _));
    EXPECT_CALL(timer, Cancel());

    baker->HandleSelect(ev, state, program, totalTime, operation);
    
    EXPECT_EQ(45, operation.baking);
}


TEST_F(StateTest, test_select_state5)
{
    Events ev = START_BUTTON_PRESSED; States state = SELECT_PROGRAM; int program = 4; int totalTime; Program operation;
    operation.baking = 40;
    baker->delayTime = 20;

    EXPECT_CALL(timer, Set(_));
    EXPECT_CALL(timer, Cancel());

    baker->HandleSelect(ev, state, program, totalTime, operation);
    
    EXPECT_EQ(START_PROGRAM, state);
}


TEST_F(StateTest, test_select_state6)
{
    Events ev = TIMER_TIMEOUT; States state = SELECT_PROGRAM; int program = 4; int totalTime; Program operation;
    operation.baking = 40;
    baker->delayTime = 20;

    EXPECT_CALL(display, DisplayOff());

    baker->HandleSelect(ev, state, program, totalTime, operation);
    
    EXPECT_EQ(STANDBY, state);
}

TEST_F(StateTest, test_prepare_state_delay0)
{
    Events ev = START_BUTTON_PRESSED; int prepState = 0; States state; int delay = 10; int totalTime = 10; int minutes = 9; Program operation; int program = 1;
    baker->delayTime = 10;

    baker->HandlePepare(ev, prepState, state, delay, totalTime, minutes, operation, program);

    EXPECT_EQ(WAITING, prepState);
}

TEST_F(StateTest, test_prepare_state_delay1)
{
    Events ev = START_BUTTON_PRESSED; int prepState = 0; States state; int delay = 9; int totalTime = 10; int minutes = 9; Program operation; int program = 1;
    baker->delayTime = 10;

    baker->HandlePepare(ev, prepState, state, delay, totalTime, minutes, operation, program);

    EXPECT_EQ(NO_INDICATOR, prepState);
    EXPECT_EQ(delay, baker->delayTime);
}

TEST_F(StateTest, test_prepare_state_waiting0)
{
    Events ev = START_BUTTON_PRESSED; int prepState = 1; States state; int delay = 10; int totalTime = 30; int minutes = 10; Program operation; int program = 1;
    baker->delayTime = 10;
    operation.waiting = 20;

    baker->HandlePepare(ev, prepState, state, delay, totalTime, minutes, operation, program);

    EXPECT_EQ(Tasks::KNEADING, prepState);
}

TEST_F(StateTest, test_prepare_state_waiting1)
{
    Events ev = START_BUTTON_PRESSED; int prepState = 1; States state; int delay = 9; int totalTime = 10; int minutes = 9; Program operation; int program = 1;
    baker->delayTime = 10;

    baker->HandlePepare(ev, prepState, state, delay, totalTime, minutes, operation, program);

    EXPECT_EQ(WAITING, prepState);
}

TEST_F(StateTest, test_prepare_state_kneading0)
{
    Events ev = START_BUTTON_PRESSED; int prepState = 2; States state; int delay = 9; int totalTime = 20; int minutes = 11; Program operation; int program = 1;
    baker->delayTime = 10;
    operation.kneading = 10;

    EXPECT_CALL(yeast, Drop(_));
    EXPECT_CALL(extras, Drop(_));
    EXPECT_CALL(motor, TurnRight());

    baker->HandlePepare(ev, prepState, state, delay, totalTime, minutes, operation, program);

    EXPECT_EQ(KNEADING, prepState);
}



TEST_F(StateTest, test_prepare_state_rising0)
{
    Events ev = START_BUTTON_PRESSED; int prepState = 3; States state; int delay = 9; int totalTime = 20; int minutes = 11; Program operation; int program = 1;

    EXPECT_CALL(oven, IsOn());
    EXPECT_CALL(oven, StartRise(_));

    baker->HandlePepare(ev, prepState, state, delay, totalTime, minutes, operation, program);

    EXPECT_EQ(RISING, prepState);
}

TEST_F(StateTest, test_prepare_state_rising1)
{
    Events ev = OVEN_DONE; int prepState = 3; States state; int delay = 9; int totalTime = 20; int minutes = 11; Program operation; int program = 1;

    baker->HandlePepare(ev, prepState, state, delay, totalTime, minutes, operation, program);

    EXPECT_EQ(BAKING, prepState);
}


TEST_F(StateTest, test_prepare_state_baking0)
{
    Events ev = TIMER_TIMEOUT; int prepState = 4; States state; int delay = 9; int totalTime = 20; int minutes = 11; Program operation; int program = 1;

    EXPECT_CALL(oven, IsOn());
    EXPECT_CALL(oven, StartBake(_));

    baker->HandlePepare(ev, prepState, state, delay, totalTime, minutes, operation, program);

    EXPECT_EQ(BAKING, prepState);
}

TEST_F(StateTest, test_prepare_state_baking1)
{
    Events ev = OVEN_DONE; int prepState = 4; States state; int delay = 9; int totalTime = 20; int minutes = 11; Program operation; int program = 1;

    baker->HandlePepare(ev, prepState, state, delay, totalTime, minutes, operation, program);

    EXPECT_EQ(DONE, prepState);
}

TEST_F(StateTest, test_prepare_state_done0)
{
    Events ev = OVEN_DONE; int prepState = 5; States state; int delay = 9; int totalTime = 20; int minutes = 11; Program operation; int program = 1;

    EXPECT_CALL(timer, Cancel());
    EXPECT_CALL(timer, Set(_));

    baker->HandlePepare(ev, prepState, state, delay, totalTime, minutes, operation, program);

    EXPECT_EQ(DONE, prepState);
}

TEST_F(StateTest, test_prepare_state_done1)
{
    Events ev = TIMER_TIMEOUT; int prepState = 5; States state; int delay = 9; int totalTime = 20; int minutes = 11; Program operation; int program = 1;

    EXPECT_CALL(timer, Cancel());
    EXPECT_CALL(display, DisplayOff());

    baker->HandlePepare(ev, prepState, state, delay, totalTime, minutes, operation, program);

    EXPECT_EQ(NO_INDICATOR, prepState);
    EXPECT_EQ(STANDBY, state);
}

TEST_F(StateTest, test_start_state0)
{
    Events ev = TIMER_TIMEOUT; int prepState; States state; int delay; int totalTime; int minutes; Program operation; int program;

    EXPECT_CALL(timer, Set(_));

    baker->HandleStart(ev, prepState, state,delay, totalTime, minutes, operation, program);
}

TEST_F(StateTest, test_start_state1)
{
    Events ev = MENU_BUTTON_LONG_PRESSED; int prepState; States state; int delay; int totalTime; int minutes; Program operation; int program;

    EXPECT_CALL(oven, IsOn());
    EXPECT_CALL(timer, Cancel());
    EXPECT_CALL(startButton, LedOff());

    baker->HandleStart(ev, prepState, state,delay, totalTime, minutes, operation, program);

    EXPECT_EQ(prepState, NO_INDICATOR);
    EXPECT_EQ(state, STANDBY);
}

TEST_F(StateTest, test_start_state2)
{
    Events ev = OVEN_DONE; int prepState; States state; int delay; int totalTime; int minutes = 10; Program operation; int program;
    int copy = minutes;

    baker->HandleStart(ev, prepState, state,delay, totalTime, minutes, operation, program);

    EXPECT_EQ(minutes, copy);
}
