
#include "BreadBaker.h"
#include "Display.h"
#include "EventGenerator.h"
#include "ExtraIngredientsTray.h"
#include "KneadMotor.h"
#include "Log.h"
#include "menu.h"
#include "Oven.h"
#include "StartButtonLed.h"
#include "Tasks.h"
#include "Timer.h"
#include "YeastTray.h"

#include <iostream>

void RespondToUserInput(char choice, IUserActions& userAction,
            IOvenSimulator& ovenSim, bool& reprintMenu, bool& quit)
{
    switch (choice)
    {
    case UserInputTimeout:
        // ignore: timeout on user input
        break;
    case MenuButtonPressed:
        userAction.MenuPressed();
        break;
    case MenuButtonLongPressed:
        userAction.MenuLongPressed();
        break;
    case TimerUpButtonPressed:
        userAction.TimerUpPressed();
        break;
    case TimerDownButtonPressed:
        userAction.TimerDownPressed();
        break;
    case StartButtonPressed:
        userAction.StartPressed();
        break;
    case SetOvenTemperatureRequest:
        std::cout << "Please enter the current temperature: ";
        int temp;
        std::cin >> temp;
        std::cin.ignore();
        ovenSim.SetTemperature(temp);
        reprintMenu = true;
        break;
    case QuitRequest:
        quit = true;
        break;
    default:
        std::cout << "I did not understand your choice (" << choice << ")\n";
        break;
    }
}

int main()
{
    Log log;
    Oven oven(log);
    Timer ovenTimer(oven, log);
    oven.AddTimer(ovenTimer);
    KneadMotor motor(log);
    YeastTray yeast(log);
    ExtraIngredientsTray extras(log);
    Display display(log);
    StartButtonLed startButton(log);
    EventGenerator eventGenerator(oven, log);
    Timer mainTimer(eventGenerator, log);
    BreadBaker baker(
                oven, mainTimer, motor, yeast, extras, display, startButton,
                eventGenerator, log);

    bool quit = false;
    bool reprintMenu = true;

    // interfaces for simulation
    IUserActions& userAction = eventGenerator;
    IOvenSimulator& ovenSim = oven;

    std::optional<char> previousChoice = std::nullopt;

    while (!quit)
    {
        if (reprintMenu)
        {
            ShowMenu();
            reprintMenu = false;
        }

        auto choice = GetUserInput();
        if (choice != std::nullopt)
        {
            if (*choice == EnterKeyPressed)
            {
                choice = previousChoice;
            }

            RespondToUserInput(*choice, userAction, ovenSim, reprintMenu, quit);

            previousChoice = choice;
        }

        if (baker.Pulse())
        {
            // this is needed for simulation only: if Pulse returns true, an
            // event was handled: now the menu needs to be reprinted.
            reprintMenu = true;
        }
    }

    return 0;
}
