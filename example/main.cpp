#include "EasyWindow.h"
#include <iostream>

int main()
{
    EasyWindow::init({.width = 1280,
                      .height = 720,
                      .title = "Custom window",
                      .resizable = true});

#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    while (!EasyWindow::shouldClose())
    {
        static bool F11Pressed = false;

        EasyWindow::GetEvents(EasyWindow::EventGettingMode::Poll);

        if (EasyWindow::isKeyPressed(GLFW_KEY_ESCAPE))
        {
            EasyWindow::requestClose();
        }
        if (EasyWindow::isKeyPressed(GLFW_KEY_F11))
        {
            if (!F11Pressed)
            {
                EasyWindow::setFullscreen(!EasyWindow::isFullscreen());
            }
            F11Pressed = true;
        }
        else
        {
            F11Pressed = false;
        }

        EasyWindow::debugPrintAllInput();
    }

    EasyWindow::close();
    return 0;
}