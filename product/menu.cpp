#include "menu.h"

#include <cstdio>
#include <iostream>
#include <sys/select.h>
#include <unistd.h>

static bool IsCharAvailable()
{
    const long TimeOutValue = 10000;

    fd_set readFds;
    FD_ZERO(&readFds);              // gives unpreventable Klocwork warning
    FD_SET(fileno(stdin), &readFds);// gives 2 unpreventable Klocwork warnings

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = TimeOutValue;

    int result = select(FD_SETSIZE, &readFds, NULL, NULL, &timeout);
    if (result < 0)
    {
        perror("Select call failed");
    }
    return result > 0;
}

void ShowMenu()
{
    std::cout << "\n\nMenu\n";
    std::cout << "====\n";
    std::cout << "(" << MenuButtonPressed << ") Menu button\n";
    std::cout << "(" << MenuButtonLongPressed << ") Menu button long press\n";
    std::cout << "(" << TimerUpButtonPressed << ") Timer up button\n";
    std::cout << "(" << TimerDownButtonPressed << ") Timer down button\n";
    std::cout << "(" << StartButtonPressed << ") Start button\n";
    std::cout << "(" << SetOvenTemperatureRequest << ") Set oven temperature\n";
    std::cout << "-----------------------\n";
    std::cout << "(" << QuitRequest << ") QUIT\n";
    std::cout << "Enter: repeat previous choice\n\n";
    std::cout << "Choice : ";
    fflush(stdout);
}

std::optional<char> GetUserInput()
{
    std::optional<char> choice = std::nullopt;

    if (IsCharAvailable())
    {
        const int MaxBufferSize = 2;
        char buf[MaxBufferSize];
        read(fileno(stdin), buf, MaxBufferSize);

        choice = buf[0];

        fflush(stdin);
    }

    return choice;
}
