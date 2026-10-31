#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace EasyWindow
{
    enum class EventGettingMode
    {
        Poll,
        Wait
    };

    void init();
    void GetEvents(EventGettingMode mode = EventGettingMode::Poll);

    // Tastatur & Maus
    bool isKeyPressed(int key);
    bool isMouseButtonPressed(int button);

    // Controller / Gamepad (Standard: jid = 0 entspricht Spieler 1)
    bool isControllerPresent(int jid = 0);
    bool isControllerButtonPressed(int button, int jid = 0);
    float getControllerAxis(int axis, int jid = 0);

    void close();
    bool shouldClose();
    void requestClose();

    // Sicherer, unveränderlicher Zugriff auf das Handle
    const GLFWwindow *getWindowHandle();
}