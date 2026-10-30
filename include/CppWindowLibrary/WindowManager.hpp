#pragma once

#include "CppWindowLibrary/Window.hpp"

#include <memory>
#include <vector>

namespace cppwindowlibrary {

class WindowManager {
public:
    WindowManager();
    ~WindowManager();

    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

    std::shared_ptr<Window> createWindow(
        int width,
        int height,
        const std::string& title,
        GLFWmonitor* monitor = nullptr,
        GLFWwindow* share = nullptr);

    void pollEvents() const;
    void removeClosedWindows();
    [[nodiscard]] bool hasOpenWindows() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Window>>& windows() const noexcept;

private:
    std::vector<std::shared_ptr<Window>> windows_;
};

}  // namespace cppwindowlibrary
