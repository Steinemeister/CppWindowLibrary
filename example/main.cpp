#include "EasyWindow.h"
#include <iostream>

int main() {
    auto& manager = WindowManager::getInstance();

    // Zwei Testfenster erstellen
    auto win1 = manager.createWindow(800, 600, "Hauptfenster (Werkzeugleiste)");
    auto win2 = manager.createWindow(400, 300, "Vorschau-Fenster");

    win1->onResize([](int width, int height) {
        std::cout << "Hauptfenster vergroessert auf: " << width << "x" << height << "\n";
    });

    win2->onResize([](int width, int height) {
        std::cout << "Vorschau-Fenster vergroessert auf: " << width << "x" << height << "\n";
    });

    // Loop starten
    manager.run();

    return 0;
}