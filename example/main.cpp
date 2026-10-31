#include <iostream>
#include "EasyWindow.h"

using namespace std;

int main() {
    cout << "Initializing EasyWindow..." << endl;
    EasyWindow::init();

    while (!EasyWindow::shouldClose()) {
        // Main loop code would go here
    }
    EasyWindow::close();
    return 0;
}