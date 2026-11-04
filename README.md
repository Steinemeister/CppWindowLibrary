# CppWindowLibrary

CppWindowLibrary provides a small, straightforward C++ API for creating a GLFW window, managing a Vulkan surface lifecycle, and reading keyboard, mouse, and controller input.

## Features

- Simple window lifecycle (`init`, `close`, `shouldClose`, `requestClose`)
- **Vulkan Support:** Check driver availability, query required instance extensions, and bind Vulkan surfaces directly.
- Polling or waiting for events
- Keyboard input helpers
- Mouse button, cursor position, and scroll delta helpers
- Gamepad presence, button, and axis helpers
- Optional terminal input monitor (`debugPrintAllInput`)

## Requirements

- CMake 3.14+
- A C++20-compatible compiler
- **Vulkan SDK** installed on your system (e.g., via LunarG installer or package manager)
- Internet access during the first configure step (GLFW is fetched automatically via CMake `FetchContent`)

### Installing Vulkan SDK via MSYS2 (UCRT64)
If you are developing on Windows using MSYS2 UCRT64, you can install the Vulkan development packages by running:
```bash
pacman -S mingw-w64-ucrt-x86_64-vulkan-devel mingw-w64-ucrt-x86_64-shaderc
```

## Integration in Other Projects (FetchContent)

You can easily integrate `CppWindowLibrary` into any existing CMake project. Add the following to your `CMakeLists.txt`:

```cmake
# 1. Look for the local Vulkan SDK
find_package(Vulkan REQUIRED)

# 2. Fetch the library from GitHub
include(FetchContent)
FetchContent_Declare(
    EasyWindow
    GIT_REPOSITORY https://github.com/Steinemeister/CppWindowLibrary.git
    GIT_TAG        v1.0.0 # Or use a specific commit hash / branch
)
FetchContent_MakeAvailable(EasyWindow)

# 3. Link it to your executable (Vulkan and GLFW include directories are inherited automatically)
add_executable(MyVulkanGame main.cpp)
target_link_libraries(MyVulkanGame PRIVATE EasyWindow::EasyWindow)
```

## Local Build & Testing

If you want to clone and build this repository locally to test the included sample application:

```bash
git clone https://github.com/Steinemeister/CppWindowLibrary.git
cd CppWindowLibrary
cmake -S . -B build
cmake --build build
```

This builds:
- `EasyWindow` (static library)
- `BeispielApp` (example executable inside `example/`)

## Usage Example (Vulkan Initialisation)

Include the umbrella header along with your Vulkan headers:

```cpp
#include "EasyWindow.h"
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>

int main() {
    // Initialise window config
    EasyWindow::init({.width = 1280, .height = 720, .title = "EasyWindow Vulkan App", .resizable = true});

    // 1. Verify Vulkan Driver Support
    if (!EasyWindow::isVulkanSupported()) {
        std::cerr << "Vulkan is not supported on this system!" << std::endl;
        EasyWindow::close();
        return -1;
    }

    // 2. Fetch required instance extensions from GLFW
    std::vector<const char*> extensions = EasyWindow::getRequiredVulkanExtensions();

    // 3. Create your VkInstance
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkInstance instance;
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        std::cerr << "Failed to create Vulkan instance!" << std::endl;
        EasyWindow::close();
        return -1;
    }

    // 4. Create the Window Surface
    VkSurfaceKHR surface;
    if (EasyWindow::createVkSurface(instance, nullptr, &surface) != VK_SUCCESS) {
        std::cerr << "Failed to create Vulkan surface!" << std::endl;
        vkDestroyInstance(instance, nullptr);
        EasyWindow::close();
        return -1;
    }

    // Main application loop
    while (!EasyWindow::shouldClose()) {
        EasyWindow::GetEvents(EasyWindow::EventGettingMode::Poll);

        if (EasyWindow::isKeyPressed(GLFW_KEY_ESCAPE)) {
            EasyWindow::requestClose();
        }
    }

    // Cleanup resources in reverse order
    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);
    EasyWindow::close();
    
    return 0;
}
```

## Public API Overview

### Window & Vulkan Management
- `void init(const WindowConfig &config)`
- `void GetEvents(EventGettingMode mode = EventGettingMode::Poll)`
- `void close()`
- `bool shouldClose()`
- `void requestClose()`
- `void setFullscreen(bool enabled)`
- `bool isFullscreen()`
- `void setResizable(bool resizable)`
- `bool isResizable()`
- `int getWidth()`
- `int getHeight()`
- `bool wasResized()`
- `GLFWwindow* getWindowHandle()`
- `bool isVulkanSupported()`
- `std::vector<const char*> getRequiredVulkanExtensions()`
- `VkResult createVkSurface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface)`

### Keyboard
- `bool isKeyPressed(int key)`

### Mouse
- `bool isMouseButtonPressed(int button)`
- `double getMouseX()`
- `double getMouseY()`
- `double getScrollX()`
- `double getScrollY()`

### Controller
- `bool isControllerPresent(int jid = 0)`
- `bool isControllerButtonPressed(int button, int jid = 0)`
- `float getControllerAxis(int axis, int jid = 0)`

### Debug
- `void debugPrintAllInput()`

## License

MIT — see [LICENSE](LICENSE).
