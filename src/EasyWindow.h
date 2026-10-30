#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>

// Repräsentiert ein einzelnes Fenster
class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool shouldClose() const;
    void makeContextCurrent();
    void swapBuffers();
    GLFWwindow* getNativeHandle() const { return m_window; }

    // Ermöglicht dem Nutzer, eigenen Code für Events zu registrieren (ohne GLFW-Boilerplate)
    void onResize(std::function<void(int, int)> callback);

private:
    GLFWwindow* m_window;
    std::function<void(int, int)> m_resizeCallback;

    // Interner GLFW-Callback, der die Brücke zu C++ schlägt
    static void sizeCallback(GLFWwindow* glfwWin, int w, int h);
};

// Verwaltet alle Fenster und den Lebenszyklus
class WindowManager {
public:
    static WindowManager& getInstance();

    // Initialisiert GLFW automatisch
    std::shared_ptr<Window> createWindow(int width, int height, const std::string& title);
    
    // Der zentrale Loop: läuft solange, wie mindestens ein Fenster offen ist
    void run();

private:
    WindowManager();
    ~WindowManager();
    
    std::vector<std::shared_ptr<Window>> m_windows;
};