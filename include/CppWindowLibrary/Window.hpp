#pragma once

#include <GLFW/glfw3.h>

#include <string>

namespace cppwindowlibrary {

class Window {
public:
    Window(int width, int height, const std::string& title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&& other) noexcept;
    Window& operator=(Window&& other) noexcept;

    [[nodiscard]] GLFWwindow* nativeHandle() const noexcept;
    [[nodiscard]] bool shouldClose() const;
    void requestClose();

    void makeContextCurrent();
    void swapBuffers();

private:
    GLFWwindow* handle_{nullptr};
};

}  // namespace cppwindowlibrary
