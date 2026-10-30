#include "CppWindowLibrary/WindowManager.hpp"

#include <algorithm>
#include <stdexcept>

namespace cppwindowlibrary {

WindowManager::WindowManager() {
    if (glfwInit() == GLFW_FALSE) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
}

WindowManager::~WindowManager() {
    windows_.clear();
    glfwTerminate();
}

std::shared_ptr<Window> WindowManager::createWindow(
    int width,
    int height,
    const std::string& title,
    GLFWmonitor* monitor,
    GLFWwindow* share) {
    auto window = std::make_shared<Window>(width, height, title, monitor, share);
    windows_.push_back(window);
    return window;
}

void WindowManager::pollEvents() const {
    glfwPollEvents();
}

void WindowManager::removeClosedWindows() {
    windows_.erase(
        std::remove_if(
            windows_.begin(),
            windows_.end(),
            [](const std::shared_ptr<Window>& window) {
                return window == nullptr || window->shouldClose();
            }),
        windows_.end());
}

bool WindowManager::hasOpenWindows() const {
    return std::any_of(
        windows_.begin(),
        windows_.end(),
        [](const std::shared_ptr<Window>& window) {
            return window != nullptr && !window->shouldClose();
        });
}

const std::vector<std::shared_ptr<Window>>& WindowManager::windows() const noexcept {
    return windows_;
}

}  // namespace cppwindowlibrary
