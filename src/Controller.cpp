#include "Controller.h"
#include <GLFW/glfw3.h>

namespace EasyWindow
{
    bool isControllerPresent(int jid)
    {
        return glfwJoystickPresent(jid) == GLFW_TRUE;
    }

    bool isControllerButtonPressed(int button, int jid)
    {
        if (!isControllerPresent(jid))
            return false;
        if (button < 0 || button > GLFW_GAMEPAD_BUTTON_LAST)
            return false;
        GLFWgamepadstate state;
        if (!glfwGetGamepadState(jid, &state) == GLFW_TRUE)
            return false;
        return state.buttons[button] == GLFW_PRESS;
    }

    float getControllerAxis(int axis, int jid)
    {
        if (!isControllerPresent(jid))
            return 0.0f;
        if (axis < 0 || axis > GLFW_GAMEPAD_AXIS_LAST)
            return 0.0f;
        GLFWgamepadstate state;
        if (!glfwGetGamepadState(jid, &state) == GLFW_TRUE)
            return 0.0f;
        return state.axes[axis];
    }
}