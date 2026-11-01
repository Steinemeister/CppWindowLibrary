#include "Mouse.h"
#include "Mouse_Internal.h"
#include "Window.h"
#include <vector>

namespace
{
    using ScrollCallback = std::function<void(double, double)>;
    std::vector<ScrollCallback> scrollCallbacks;

    double currentScrollX = 0.0;
    double currentScrollY = 0.0;

    void GLFW_ScrollBridge(GLFWwindow *window, double xoffset, double yoffset)
    {
        (void)window;

        for (const auto &callback : scrollCallbacks)
        {
            callback(xoffset, yoffset);
        }
        currentScrollX += xoffset;
        currentScrollY += yoffset;
    }
}

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

    double getScrollX()
    {
        return currentScrollX;
    }

    double getScrollY()
    {
        return currentScrollY;
    }
}

namespace EasyWindow::Internal
{
    void InitMouseCallbacks(GLFWwindow *window)
    {
        glfwSetScrollCallback(window, GLFW_ScrollBridge);
    }

    void ResetScrollDeltas()
    {
        currentScrollX = 0.0;
        currentScrollY = 0.0;
    }
}