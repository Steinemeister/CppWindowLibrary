#include "Mouse.h"
#include "Window.h"

namespace EasyWindow
{
    bool isMouseButtonPressed(int button)
    {
        const GLFWwindow *windowHandle = getWindowHandle();
        if (!windowHandle)
        {
            return false;
        }
        int state = glfwGetMouseButton(const_cast<GLFWwindow *>(windowHandle), button);
        return state == GLFW_PRESS;
    }

    double getMouseX()
    {
        const GLFWwindow *windowHandle = getWindowHandle();
        if (!windowHandle)
        {
            return 0.0;
        }
        double x, y;
        glfwGetCursorPos(const_cast<GLFWwindow *>(windowHandle), &x, &y);
        return x;
    }

    double getMouseY()
    {
        const GLFWwindow *windowHandle = getWindowHandle();
        if (!windowHandle)
        {
            return 0.0;
        }
        double x, y;
        glfwGetCursorPos(const_cast<GLFWwindow *>(windowHandle), &x, &y);
        return y;
    }
}