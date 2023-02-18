#ifndef MENU_H
#define MENU_H

#include <optional>


const char UserInputTimeout = '\0';
const char EnterKeyPressed = 10;
const char MenuButtonPressed = '1';
const char MenuButtonLongPressed = '2';
const char TimerUpButtonPressed = '3';
const char TimerDownButtonPressed = '4';
const char StartButtonPressed = '5';
const char SetOvenTemperatureRequest = '6';
const char QuitRequest = 'q';

void ShowMenu();
std::optional<char> GetUserInput();

#endif
