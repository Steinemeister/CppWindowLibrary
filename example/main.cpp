#include "EasyWindow.h"
#include <iostream>
#include <vector>

// Vulkan-Header direkt im Hauptprogramm inkludieren
#include <vulkan/vulkan.h>

int main()
{
    EasyWindow::init({.width = 1280,
                      .height = 720,
                      .title = "Custom window (Vulkan)",
                      .resizable = true});

#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    // 1. Prüfen, ob Vulkan überhaupt unterstützt wird
    if (!EasyWindow::isVulkanSupported())
    {
        std::cerr << "Kritischer Fehler: Vulkan wird auf diesem System nicht unterstuetzt!" << std::endl;
        EasyWindow::close();
        return -1;
    }
    std::cout << "[Vulkan] Treiber-Support erfolgreich verifiziert.\n";

    // 2. Benötigte Window-Extensions von deiner Library abfragen
    std::vector<const char *> extensions = EasyWindow::getRequiredVulkanExtensions();

    // 3. Vulkan-Instanz (VkInstance) konfigurieren und erstellen
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "EasyWindow Vulkan App";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();
    createInfo.enabledLayerCount = 0; // Für echtes Debugging später z.B. Validation Layers nutzen

    VkInstance instance;
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
    {
        std::cerr << "Kritischer Fehler: Vulkan-Instanz konnte nicht erstellt werden!" << std::endl;
        EasyWindow::close();
        return -1;
    }
    std::cout << "[Vulkan] VkInstance erfolgreich erstellt.\n";

    // 4. Vulkan-Surface erstellen (Verbindung von Fenster und Vulkan)
    VkSurfaceKHR surface;
    if (EasyWindow::createVulkanSurface(instance, nullptr, &surface) != VK_SUCCESS)
    {
        std::cerr << "Kritischer Fehler: Vulkan-Surface konnte nicht erstellt werden!" << std::endl;
        vkDestroyInstance(instance, nullptr);
        EasyWindow::close();
        return -1;
    }
    std::cout << "[Vulkan] VkSurfaceKHR erfolgreich an das Fenster gebunden.\n";

    // --- DEINE BESTEHENDE RENDER- / EVENT-SCHLEIFE ---
    while (!EasyWindow::shouldClose())
    {
        static bool F11Pressed = false;

        EasyWindow::GetEvents(EasyWindow::EventGettingMode::Poll);

        if (EasyWindow::isKeyPressed(GLFW_KEY_ESCAPE))
        {
            EasyWindow::requestClose();
        }
        if (EasyWindow::isKeyPressed(GLFW_KEY_F11))
        {
            if (!F11Pressed)
            {
                EasyWindow::setFullscreen(!EasyWindow::isFullscreen());
            }
            F11Pressed = true;
        }
        else
        {
            F11Pressed = false;
        }

        // Hier könntest du deine Vulkan-Rendering-Funktionen aufrufen

        // Optional: Debug-Ausgabe aller Eingaben
        // EasyWindow::debugPrintAllInput();
    }

    // 5. Aufräumen (In umgekehrter Reihenfolge zur Erstellung)
    std::cout << "[Vulkan] Raeume Ressourcen auf...\n";
    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);

    EasyWindow::close();
    return 0;
}