#include "EasyWindow.h"
#include <iostream>

// --- WINDOW IMPLEMENTATION ---
Window::Window(int width, int height, const std::string& title) {
    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Fehler: Fenster konnte nicht erstellt werden!" << std::endl;
        return;
    }

    // WICHTIG: C++ Instanz an das GLFW-Fenster koppeln
    glfwSetWindowUserPointer(m_window, this);

    // Internen C-Callback für Größenänderung registrieren
    glfwSetFramebufferSizeCallback(m_window, Window::sizeCallback);
}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void Window::makeContextCurrent() {
    glfwMakeContextCurrent(m_window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_window);
}

void Window::onResize(std::function<void(int, int)> callback) {
    m_resizeCallback = callback;
}

void Window::sizeCallback(GLFWwindow* glfwWin, int w, int h) {
    // Hole das C++ Window-Objekt zurück
    auto* instance = static_cast<Window*>(glfwGetWindowUserPointer(glfwWin));
    if (instance && instance->m_resizeCallback) {
        instance->m_resizeCallback(w, h); // Nutzer-Callback ausführen
    }
}

// --- WINDOW MANAGER IMPLEMENTATION ---
WindowManager::WindowManager() {
    if (!glfwInit()) {
        std::cerr << "Fehler: GLFW konnte nicht initialisiert werden!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

WindowManager::~WindowManager() {
    glfwTerminate();
}

WindowManager& WindowManager::getInstance() {
    static WindowManager instance;
    return instance;
}

std::shared_ptr<Window> WindowManager::createWindow(int width, int height, const std::string& title) {
    auto window = std::make_shared<Window>(width, height, title);
    m_windows.push_back(window);
    return window;
}

void WindowManager::run() {
    while (!m_windows.empty()) {
        glfwPollEvents();

        // Über alle Fenster iterieren (rückwärts, falls wir eins löschen)
        for (auto it = m_windows.begin(); it != m_windows.end();) {
            auto window = *it;

            if (window->shouldClose()) {
                it = m_windows.erase(it); // Fenster aus der Verwaltung werfen -> Destruktor schließt es
            } else {
                // Zeichnen für dieses spezifische Fenster
                window->makeContextCurrent();
                window->swapBuffers();
                ++it;
            }
        }
    }
}