#include "Window.h"
#include <iostream>

namespace EasyWindow
{
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

    const GLFWwindow *getWindowHandle()
    {
        return window;
    }
}