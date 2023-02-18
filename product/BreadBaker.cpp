#include "BreadBaker.h"
#include "Program.h"
#include "TimeConstants.h"

BreadBaker::BreadBaker(
    IOven &oven, ITimer &timer, IKneadMotor &motor, IYeastTray &yeast,
    IExtraIngredientsTray &extras, IDisplay &display,
    IStartButtonLed &startButton, IEventGenerator &eventGenerator,
    Log &log)
    : oven(oven), timer(timer), motor(motor), yeast(yeast), extras(extras), display(display), startButton(startButton), eventGenerator(eventGenerator), log(log)
{
    delayTime = 0;
}

bool BreadBaker::Pulse()
{
    auto ev = eventGenerator.GetEvent();
    if (ev != std::nullopt)
    {
        HandleEvent(*ev);
    }
    return ev != std::nullopt;
}

void BreadBaker::HandleStandby(Events ev, States &state)
{
    static int iterations = 0;
    static bool fromTimeout = false;

    switch (ev)
    {
    case MENU_BUTTON_PRESSED:
    {
        if (oven.GetTemperature() > 50)
        {
            timer.Set(0);
            fromTimeout = true;
            break;
        }
        else
        {
            state = States::SELECT_PROGRAM;
        }

        break;
    }

    case TIMER_TIMEOUT:
    {
        if (fromTimeout == true)
        {
            if (iterations % 2 == 0)
            {
                startButton.LedOn();
            }
            else
            {
                startButton.LedOff();
            }
            iterations++;

            if (iterations == 20)
            {
                iterations = 0;
                fromTimeout = false;
                break;
            }

        }
        timer.Set(MIN);

        break;
    }

    default:

        break;
    }
}

void BreadBaker::HandleSelect(Events ev, States &state, int &program, int &totalTime, Program &operation)
{
    switch (ev)
    {
    case MENU_BUTTON_PRESSED:
    {
        timer.Set(MIN * 5);

        // start the delay timer from 0 for each program switch
        delayTime = 0;

        HandleSelectProgram(operation, program, totalTime);

        if (program != 4)
        {
            display.SetTime(totalTime / 60, totalTime % 60);
        }
        else
        {
            display.SetTime(operation.baking / 60, operation.baking % 60);
        }

        display.SetMenu(program);
        timer.Cancel();

        break;
    }

    case TIMER_DOWN_BUTTON_PRESSED:
    {
        display.SetMenu(program);

        if (program != 4)
        {
            if (delayTime > 0)
            {
                delayTime -= 10;
            }
            display.SetTime(totalTime / 60, totalTime % 60);
            log.Trace("Delayed Start: %d:%d", delayTime / 60, delayTime % 60);
        }
        else
        {
            if (operation.baking > 30)
            {
                operation.baking -= 5;
            }

            display.SetTime(operation.baking / 60, operation.baking % 60);
        }

        timer.Cancel();
        break;
    }

    case TIMER_UP_BUTTON_PRESSED:
    {
        display.SetMenu(program);

        if (program != 4)
        {
            if (delayTime < 720)
            {
                delayTime += 10;
            }
            display.SetTime(totalTime / 60, totalTime % 60);
            log.Trace("Delayed Start: %d:%d", delayTime / 60, delayTime % 60);
        }
        else
        {
            if (operation.baking < 90)
            {
                operation.baking += 5;
            }

            display.SetTime(operation.baking / 60, operation.baking % 60);
        }

        timer.Cancel();
        break;
    }

    case START_BUTTON_PRESSED:
    {
        state = States::START_PROGRAM;
        timer.Cancel();
        timer.Set(1); // precondition to start the START PROGRAM
        break;
    }

    case TIMER_TIMEOUT:
    {
        state = States::STANDBY;
        display.DisplayOff();
        break;
    }

    default:

        break;
    }
}

void BreadBaker::HandleSelectProgram(Program &operation, int &program, int &totalTime)
{

    ++program;

    if (program == 5)
    {
        program = 0;
    }

    switch (program)
    {
    case 0:
        operation.waiting = 60;
        operation.kneading = 20;
        operation.rising = 160;
        operation.baking = 50;
        operation.addYeast = true;
        operation.addExtras = false;

        totalTime = 290;

        break;

    case 1:
        operation.waiting = 60;
        operation.kneading = 20;
        operation.rising = 160;
        operation.baking = 50;
        operation.addYeast = true;
        operation.addExtras = true;

        totalTime = 290;

        break;

    case 2:
        operation.waiting = 0;
        operation.kneading = 15;
        operation.rising = 60;
        operation.baking = 40;
        operation.addExtras = false;
        operation.addYeast = false;

        totalTime = 115;

        break;

    case 3:
        operation.waiting = 40;
        operation.kneading = 15;
        operation.rising = 60;
        operation.baking = 0;
        operation.addExtras = false;
        operation.addYeast = false;

        totalTime = 140;

        break;

    case 4:

        operation.waiting = 0;
        operation.kneading = 0;
        operation.rising = 0;
        // if coming from case 3
        if (operation.baking == 0)
        {
            operation.baking = 30;
        }
        operation.addExtras = false;
        operation.addYeast = false;

        totalTime = operation.baking;

        break;

    default:
        break;
    }
}

void BreadBaker::HandlePepare(Events ev, int &prepState, States &state, int &delay, int &totalTime, int &minutes, Program &operation, int &program)
{
    switch (prepState)
    {
    case NO_INDICATOR:
    {
        log.Trace("Program strats in: %d:%d\n", (delayTime - delay) / 60, (delayTime - delay) % 60);

        if (delay == delayTime)
        {
            delay = 0;
            delayTime = 0;
            prepState = WAITING;
        }

        delay += 1;

        break;
    }

    case WAITING:
    {
        log.Debug("Waiting");

        if (minutes == totalTime - operation.waiting || operation.waiting == 0)
        {
            prepState = KNEADING;
        }
        break;
    }

    case KNEADING:
    {
        static bool once = false;
        static bool reverse = false;

        log.Debug("Kneading");
        if ((minutes == totalTime - (operation.kneading + operation.waiting)) || operation.kneading == 0)
        {
            prepState = RISING;
            motor.Stop();
            once = false;
            break;
        }

        if (reverse)
        {
            motor.TurnLeft();
        }
        else
        {
            motor.TurnRight();
        }

        reverse = !reverse;

        if (!once)
        {
            if (program == 1)
            {
                extras.Drop(15 * MIN);
            }

            yeast.Drop(((operation.kneading / 2) * MIN) / 60); // prints minutes to screen and not seconds

            once = true;
        }

        break;
    }

    case RISING:
    {
        if (operation.rising == 0)
        {
            prepState = BAKING;
            break;
        }

        if (ev == OVEN_DONE)
        {
            prepState = BAKING;
            minutes = operation.baking;
        }
        else
        {
            if (!oven.IsOn())
            {
                oven.StartRise(operation.rising);
            }
        }
        break;
    }

    case BAKING:
    {
        if (operation.baking == 0)
        {
            prepState = DONE;
            break;
        }

        if (ev == OVEN_DONE)
        {
            prepState = DONE;
            minutes = 0;
        }
        else
        {
            if(!oven.IsOn())
            {
                minutes = operation.baking;
                oven.StartBake(operation.baking);
            }
        }
        break;
    }

    case DONE:
    {
        switch (ev)
        {
        case TIMER_TIMEOUT:
        {
            state = STANDBY;
            prepState = NO_INDICATOR;
            display.DisplayOff();
            timer.Cancel();
            minutes = 0;
            delayTime = 0;
            delay = 0;
            break;
        }

        default:
            timer.Cancel();
            timer.Set(5 * MIN);
            break;
        }

        break;
    }

    default:
        // nothing tbd
        break;
    }
}

void BreadBaker::HandleStart(Events ev, int &prepState, States &state, int &delay, int &totalTime, int &minutes, Program &operation, int &program)
{
    switch (ev)
    {
    case OVEN_DONE: //go into Timer Timeout anyways
    case TIMER_TIMEOUT:
    {

        if (ev != 6)
        {
            timer.Set(MIN);
            minutes -= 1;
        }
        
        HandlePepare(ev, prepState, state, delay, totalTime, minutes, operation, program);

        break;
    }

    case MENU_BUTTON_LONG_PRESSED:
    {
        state = STANDBY;
        if (oven.IsOn())
        {
            oven.Cancel();
        }
        timer.Cancel();
        prepState = NO_INDICATOR;
        startButton.LedOff();
        minutes = 0;
        delayTime = 0;
        delay = 0;
        break;
    }

    default:
    {
        // nothing tbd
        break;
    }
    }
}

// parameter name in comment to prevent compiler warning as it is unused for now
void BreadBaker::HandleEvent(Events ev)
{
    static States state = States::STANDBY;
    static int program = 0;
    static int totalTime = 0;
    static Program operation;

    switch (state)
    {
    case STANDBY:
    {
        HandleStandby(ev, state);
        break;
    }

    case SELECT_PROGRAM:
    {
        display.SetCurrentTask(Tasks::NO_INDICATOR);

        HandleSelect(ev, state, program, totalTime, operation);

        break;
    }

    case START_PROGRAM:
    {
        static int prepState = NO_INDICATOR;
        startButton.LedOn(); // turn on LED
        static int minutes = totalTime;
        if (minutes == 0)
        {
            minutes += totalTime;
        }
        static int delay = 0;
        if (delayTime == 0)
            display.SetTime(minutes / 60, minutes % 60);
        display.SetCurrentTask((Tasks)prepState);
        display.SetMenu(program);


        HandleStart(ev, prepState, state, delay, totalTime, minutes, operation, program);
        break;
    }
    }
}