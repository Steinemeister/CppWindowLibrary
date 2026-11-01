#include "EasyWindow.h"
#include <iostream>

int main()
{
    EasyWindow::init();

    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif

    while (!EasyWindow::shouldClose())
    {
        EasyWindow::GetEvents(EasyWindow::EventGettingMode::Poll);

        if (EasyWindow::isKeyPressed(GLFW_KEY_ESCAPE))
        {
            EasyWindow::requestClose();
        }
        if (EasyWindow::isControllerPresent(GLFW_JOYSTICK_1) && EasyWindow::isControllerButtonPressed(GLFW_JOYSTICK_1, GLFW_GAMEPAD_BUTTON_BACK))
        {
            EasyWindow::requestClose();
        }

        EasyWindow::debugPrintAllInput(); 
    }

    EasyWindow::close();
    return 0;
}