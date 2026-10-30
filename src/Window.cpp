#include "CppWindowLibrary/Window.hpp"

#include <stdexcept>
#include <utility>

namespace cppwindowlibrary {

Window::Window(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share)
    : handle_(glfwCreateWindow(width, height, title.c_str(), monitor, share)) {
    if (handle_ == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
    }
}

Window::~Window() {
    if (handle_ != nullptr) {
        glfwDestroyWindow(handle_);
    }
}

Window::Window(Window&& other) noexcept : handle_(std::exchange(other.handle_, nullptr)) {}

Window& Window::operator=(Window&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    if (handle_ != nullptr) {
        glfwDestroyWindow(handle_);
    }

    handle_ = std::exchange(other.handle_, nullptr);
    return *this;
}

GLFWwindow* Window::nativeHandle() const noexcept {
    return handle_;
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(handle_) != 0;
}

void Window::requestClose() {
    glfwSetWindowShouldClose(handle_, GLFW_TRUE);
}

void Window::makeContextCurrent() {
    glfwMakeContextCurrent(handle_);
}

void Window::swapBuffers() {
    glfwSwapBuffers(handle_);
}

}  // namespace cppwindowlibrary
