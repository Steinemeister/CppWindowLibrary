#pragma once
#include <string_view>
#include <vector>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


namespace EasyWindow
{
    enum class EventGettingMode
    {
        Poll,
        Wait
    };

    struct WindowConfig
    {
        int width = 800;
        int height = 600;
        std::string_view title = "Easy Window";
        bool fullscreen = false;
        bool resizable = true;
    };

    void init(const WindowConfig &config = WindowConfig{});
    void GetEvents(EventGettingMode mode = EventGettingMode::Poll);

    void close();
    bool shouldClose();
    void requestClose();

    void setFullscreen(bool enabled);
    void setResizable(bool resizable);

    bool isFullscreen();
    bool isResizable();

    int getWidth();
    int getHeight();
    bool wasResized();

    GLFWwindow *getWindowHandle();

    std::vector<const char *> getRequiredVulkanExtensions();
    VkResult createVulkanSurface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface);

    bool isVulkanSupported();
}