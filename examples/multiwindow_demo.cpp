#include "CppWindowLibrary/WindowManager.hpp"

int main() {
    cppwindowlibrary::WindowManager manager;

    auto first = manager.createWindow(640, 480, "First GLFW Window");
    auto second = manager.createWindow(640, 480, "Second GLFW Window");

    while (manager.hasOpenWindows()) {
        manager.pollEvents();

        if (first != nullptr && !first->shouldClose()) {
            first->makeContextCurrent();
            first->swapBuffers();
        }

        if (second != nullptr && !second->shouldClose()) {
            second->makeContextCurrent();
            second->swapBuffers();
        }

        manager.removeClosedWindows();
    }

    return 0;
}
