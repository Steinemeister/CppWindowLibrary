#pragma once
#include <GLFW/glfw3.h>

namespace EasyWindow
{
    enum class EventGettingMode
    {
        Poll,
        Wait
    };

    void init();
    void GetEvents(EventGettingMode mode = EventGettingMode::Poll);

    void close();
    bool shouldClose();
    void requestClose();

    // Sicherer, unveränderlicher Zugriff auf das Handle
    const GLFWwindow *getWindowHandle();
}