#include "EasyWindow.h"
#include <iostream>

namespace EasyWindow
{
    // Versteckte, globale Variable (nur in dieser Datei sichtbar)
    static GLFWwindow *window = nullptr;

    void init()
    {
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return;
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        window = glfwCreateWindow(800, 600, "Easy Window", nullptr, nullptr);
        if (!window)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);
    }

    void close()
    {
        if (window)
        {
            glfwDestroyWindow(window);
            window = nullptr;
        }
        glfwTerminate();
    }

    void requestClose()
    {
        if (window)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

    bool shouldClose()
    {
        return window && glfwWindowShouldClose(window);
    }

    void GetEvents(EventGettingMode mode)
    {
        if (mode == EventGettingMode::Poll)
        {
            glfwPollEvents();
        }
        else
        {
            glfwWaitEvents();
        }
    }

    bool isKeyPressed(int key)
    {
        return window && glfwGetKey(window, key) == GLFW_PRESS;
    }

    bool isMouseButtonPressed(int button)
    {
        return window && glfwGetMouseButton(window, button) == GLFW_PRESS;
    }

    bool isControllerPresent(int jid)
    {
        // Rechnet den benutzerfreundlichen Index (0, 1...) in GLFW-IDs um
        int glfwJid = GLFW_JOYSTICK_1 + jid;

        if (glfwJid < GLFW_JOYSTICK_1 || glfwJid > GLFW_JOYSTICK_LAST)
        {
            return false;
        }
        if (!glfwJoystickPresent(glfwJid))
        {
            return false;
        }
        return glfwJoystickIsGamepad(glfwJid);
    }

    bool isControllerButtonPressed(int button, int jid)
    {
        if (!isControllerPresent(jid))
        {
            return false;
        }
        // Exakte Index-Grenze: button darf bis inklusive GLFW_GAMEPAD_BUTTON_LAST gehen
        if (button < 0 || button > GLFW_GAMEPAD_BUTTON_LAST)
        {
            return false;
        }

        int glfwJid = GLFW_JOYSTICK_1 + jid;
        GLFWgamepadstate state;
        if (glfwGetGamepadState(glfwJid, &state))
        {
            return state.buttons[button] == GLFW_PRESS;
        }
        return false;
    }

    float getControllerAxis(int axis, int jid)
    {
        if (!isControllerPresent(jid))
        {
            return 0.0f;
        }
        // Exakte Index-Grenze: axis darf bis inklusive GLFW_GAMEPAD_AXIS_LAST gehen
        if (axis < 0 || axis > GLFW_GAMEPAD_AXIS_LAST)
        {
            return 0.0f;
        }

        int glfwJid = GLFW_JOYSTICK_1 + jid;
        GLFWgamepadstate state;
        if (glfwGetGamepadState(glfwJid, &state))
        {
            return state.axes[axis];
        }
        return 0.0f;
    }

    const GLFWwindow *getWindowHandle()
    {
        return window;
    }
}