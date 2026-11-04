#include "Window.h"
#include "Mouse_Internal.h"
#include <iostream>
#include <vector>

namespace EasyWindow
{
    static GLFWwindow *window = nullptr;

    static int windowedX = 100;
    static int windowedY = 100;
    static int windowedWidth = 800;
    static int windowedHeight = 600;

    static bool resizedLastFrame = false;

    static void GLFW_FramebufferSizeBridge(GLFWwindow *window, int width, int height)
    {
        (void)window;
        (void)width;
        (void)height;
        resizedLastFrame = true;
    }

    void init(const WindowConfig &config)
    {
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return;
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        glfwWindowHint(GLFW_RESIZABLE, config.resizable ? GLFW_TRUE : GLFW_FALSE);

        GLFWmonitor *primaryMonitor = config.fullscreen ? glfwGetPrimaryMonitor() : nullptr;

        window = glfwCreateWindow(config.width, config.height,
                                  config.title.data(), primaryMonitor, nullptr);
        if (!window)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        if (!config.fullscreen)
        {
            glfwGetWindowPos(window, &windowedX, &windowedY);
            glfwGetWindowSize(window, &windowedWidth, &windowedHeight);
        }

        glfwSetFramebufferSizeCallback(window, GLFW_FramebufferSizeBridge);

        Internal::InitMouseCallbacks(window);
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
        Internal::ResetScrollDeltas();
        resizedLastFrame = false;

        if (mode == EventGettingMode::Poll)
        {
            glfwPollEvents();
        }
        else
        {
            glfwWaitEvents();
        }
    }

    void setFullscreen(bool enabled)
    {
        if (!window)
            return;

        if (!window)
            return;

        bool isFullscreen = (glfwGetWindowMonitor(window) != nullptr);
        if (enabled == isFullscreen)
            return;

        if (enabled)
        {
            glfwGetWindowPos(window, &windowedX, &windowedY);
            glfwGetWindowSize(window, &windowedWidth, &windowedHeight);

            GLFWmonitor *monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);

            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        else
        {
            glfwSetWindowMonitor(window, nullptr, windowedX, windowedY, windowedWidth, windowedHeight, 0);
        }
    }

    void setResizable(bool resizable)
    {
        if (!window)
            return;

        glfwSetWindowAttrib(window, GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
    }

    bool isFullscreen()
    {
        if (!window)
            return false;
        return glfwGetWindowMonitor(window) != nullptr;
    }

    bool isResizable()
    {
        if (!window)
            return false;
        return glfwGetWindowAttrib(window, GLFW_RESIZABLE) == GLFW_TRUE;
    }

    int getWidth()
    {
        if (!window)
            return 0;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        return width;
    }

    int getHeight()
    {
        if (!window)
            return 0;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        return height;
    }

    std::vector<const char *> getRequiredVulkanExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        if (!glfwExtensions)
        {
            return {};
        }

        return std::vector<const char *>(glfwExtensions, glfwExtensions + glfwExtensionCount);
    }

    VkResult createVulkanSurface(VkInstance instance, const VkAllocationCallbacks *allocator, VkSurfaceKHR *surface)
    {
        if (!window)
            return VK_ERROR_INITIALIZATION_FAILED;

        return glfwCreateWindowSurface(instance, window, allocator, surface);
    }

    bool isVulkanSupported()
    {
        return glfwVulkanSupported() == GLFW_TRUE;
    }

    bool wasResized() { return resizedLastFrame; }

    GLFWwindow *getWindowHandle()
    {
        return window;
    }
}