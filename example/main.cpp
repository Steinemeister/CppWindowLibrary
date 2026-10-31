#include "EasyWindow.h"
#include <iostream>
#include <cmath>

int main()
{
    EasyWindow::init();

    std::cout << "Library erfolgreich gestartet!" << std::endl;

    while (!EasyWindow::shouldClose())
    {
        EasyWindow::GetEvents(EasyWindow::EventGettingMode::Poll);

        // Schließen mit der ESC-Taste auf der Tastatur
        if (EasyWindow::isKeyPressed(GLFW_KEY_ESCAPE))
        {
            EasyWindow::requestClose();
        }

        // Controller-Abfrage für Spieler 1 (nutzt automatisch jid = 0)
        if (EasyWindow::isControllerPresent())
        {
            // Digitaler Button-Test (Xbox: A / PlayStation: X)
            bool aGedrueckt = EasyWindow::isControllerButtonPressed(GLFW_GAMEPAD_BUTTON_A);
            
            // Analoger Stick-Test (Linker Stick, X-Achse)
            float stickX = EasyWindow::getControllerAxis(GLFW_GAMEPAD_AXIS_LEFT_X);

            // Live-Status in der gleichen Zeile ausgeben
            std::cout << "Controller aktiv! Button A: " << (aGedrueckt ? "GEPRESST" : "---") 
                      << " | Stick X: " << stickX << "    \r" << std::flush;

            if (aGedrueckt)
            {
                std::cout << "\n[EVENT] Button A wurde registriert!" << std::endl;
            }
        }
        else
        {
            std::cout << "Warte auf Controller...                      \r" << std::flush;
        }
    }

    EasyWindow::close();
    std::cout << "\nLibrary sauber beendet." << std::endl;
    return 0;
}