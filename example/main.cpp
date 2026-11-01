#include "EasyWindow.h"
#include <iostream>

int main()
{
    EasyWindow::init();

    // Einmalig das Terminal leeren, damit die Formatierung sauber greift
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

        EasyWindow::debugPrintAllInput(); 
    }

    EasyWindow::close();
    return 0;
}