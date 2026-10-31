#include "EasyWindow.h"
#include <iostream>

namespace EasyWindow
{
    GLFWwindow* window;

    void init()
    {
        glfwSetErrorCallback([](int error, const char *description)
                             { std::cerr << "GLFW Error (" << error << "): " << description << std::endl; });

        std::cout << "Initializing GLFW..." << std::endl;

        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "Creating GLFW window..." << std::endl;

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        window = glfwCreateWindow(800, 600, "EasyWindow", nullptr, nullptr);
        if (!window)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
    }

    void close()
    {
        std::cout << "Closing GLFW window..." << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void requestClose()
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    bool shouldClose()
    {
        return glfwWindowShouldClose(window);
    }
}