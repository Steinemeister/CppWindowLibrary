#include "Debug.h"
#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Controller.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <iomanip>
#include <cmath>

namespace EasyWindow
{

    constexpr std::string_view TITLE = "EASYWINDOW INPUT MONITOR";
    constexpr int MIN_WIDTH = 72;

    struct BoxLayout
    {
        int width;
        int paddingLeft;
        int paddingRight;

        constexpr BoxLayout() : width(0), paddingLeft(0), paddingRight(0)
        {
            int textLength = static_cast<int>(TITLE.length());
            int requiredWidth = textLength + 4;
            width = (requiredWidth > MIN_WIDTH) ? requiredWidth : MIN_WIDTH;

            int internalSpace = width - 4;
            paddingLeft = (internalSpace - textLength) / 2;
            paddingRight = internalSpace - textLength - paddingLeft;
        }
    };

    constexpr BoxLayout LAYOUT;

    static const char *formatBtn(bool pressed)
    {
        return pressed ? "[X]" : "[ ]";
    }

    static void printLine(char ch)
    {
        for (int i = 0; i < LAYOUT.width; ++i)
        {
            std::cout << ch;
        }
        std::cout << "\n";
    }

    static void printWindowSection()
    {
        std::cout << "[WINDOW]\n";
        std::cout << "  Size:       " << std::setw(4) << getWidth() << " x " << std::setw(4) << getHeight() << " Pixels\n";
        std::cout << "  State:      Fullscreen: " << formatBtn(isFullscreen()) 
                  << " | Resizable: " << formatBtn(isResizable()) << "\n";

        // Resize-Event für ein paar Frames über die Checkbox halten
        static int resizeDisplayTimer = 0;
        if (wasResized())
        {
            resizeDisplayTimer = 15;
        }

        // Steuert das [X] oder [ ] basierend auf dem Timer
        bool showResized = (resizeDisplayTimer > 0);
        if (showResized)
        {
            resizeDisplayTimer--;
        }

        std::cout << "  Event:      Resized: " << formatBtn(showResized) << "                                       \n";
    }

    static void printKeyboardSection()
    {
        std::cout << "[KEYBOARD]\n";
        std::cout << "  ESC:   " << formatBtn(isKeyPressed(GLFW_KEY_ESCAPE)) << " | "
                  << "SPACE: " << formatBtn(isKeyPressed(GLFW_KEY_SPACE)) << " | "
                  << "W-A-S-D: "
                  << (isKeyPressed(GLFW_KEY_W) ? "W" : "_") << (isKeyPressed(GLFW_KEY_A) ? "A" : "_")
                  << (isKeyPressed(GLFW_KEY_S) ? "S" : "_") << (isKeyPressed(GLFW_KEY_D) ? "D" : "_") << "    \n";
    }

    static void printMouseSection()
    {
        std::cout << "[MOUSE]\n";
        std::cout << "  Buttons:  Left: " << formatBtn(isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
                  << " Right: " << formatBtn(isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) << "    \n";

        std::cout << std::fixed << std::setprecision(1);
        std::cout << "  Position: X: " << std::setw(6) << getMouseX()
                  << " Y: " << std::setw(6) << getMouseY() << "    \n";

        static double displayScrollX = 0.0;
        static double displayScrollY = 0.0;

        double currentX = getScrollX();
        double currentY = getScrollY();

        // Wenn in diesem Frame gescrollt wurde, nimm den neuen Wert
        if (currentX != 0.0) displayScrollX = currentX;
        if (currentY != 0.0) displayScrollY = currentY;

        // Zeige den geglätteten/gehaltenen Wert an
        std::cout << "  Scroll:   X: " << std::setw(6) << displayScrollX
                  << " Y: " << std::setw(6) << displayScrollY << "    \n";

        // Lass den Wert langsam gegen 0 wandern (Interpolation), damit er nicht sofort wegspringt
        displayScrollX *= 0.9; 
        displayScrollY *= 0.9;

        // Schneide winzige Werte ab, um permanentes "0.0" zu garantieren
        if (std::abs(displayScrollX) < 0.05) displayScrollX = 0.0;
        if (std::abs(displayScrollY) < 0.05) displayScrollY = 0.0;
    }

    static void printSingleController(int jid)
    {
        int glfwJid = GLFW_JOYSTICK_1 + jid;
        std::cout << "  -> Player " << (jid + 1) << " (" << glfwGetJoystickName(glfwJid) << "):          \n";

        std::cout << "     Buttons: A:" << formatBtn(isControllerButtonPressed(GLFW_GAMEPAD_BUTTON_A, jid))
                  << " B:" << formatBtn(isControllerButtonPressed(GLFW_GAMEPAD_BUTTON_B, jid))
                  << " X:" << formatBtn(isControllerButtonPressed(GLFW_GAMEPAD_BUTTON_X, jid))
                  << " Y:" << formatBtn(isControllerButtonPressed(GLFW_GAMEPAD_BUTTON_Y, jid)) << " | "
                  << "LB:" << formatBtn(isControllerButtonPressed(GLFW_GAMEPAD_BUTTON_LEFT_BUMPER, jid))
                  << " RB:" << formatBtn(isControllerButtonPressed(GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER, jid)) << "    \n";

        std::cout << "     D-Pad:   Up:" << formatBtn(isControllerButtonPressed(GLFW_GAMEPAD_BUTTON_DPAD_UP, jid))
                  << " Down:" << formatBtn(isControllerButtonPressed(GLFW_GAMEPAD_BUTTON_DPAD_DOWN, jid))
                  << " Left:" << formatBtn(isControllerButtonPressed(GLFW_GAMEPAD_BUTTON_DPAD_LEFT, jid))
                  << " Right:" << formatBtn(isControllerButtonPressed(GLFW_GAMEPAD_BUTTON_DPAD_RIGHT, jid)) << "    \n";

        float lx = getControllerAxis(GLFW_GAMEPAD_AXIS_LEFT_X, jid);
        float ly = getControllerAxis(GLFW_GAMEPAD_AXIS_LEFT_Y, jid);
        float rx = getControllerAxis(GLFW_GAMEPAD_AXIS_RIGHT_X, jid);
        float ry = getControllerAxis(GLFW_GAMEPAD_AXIS_RIGHT_Y, jid);
        float lTrig = getControllerAxis(GLFW_GAMEPAD_AXIS_LEFT_TRIGGER, jid);
        float rTrig = getControllerAxis(GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER, jid);

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "     L-Stick: X: " << std::setw(5) << lx
                  << " Y: " << std::setw(5) << ly << " | "
                  << "R-Stick: X: " << std::setw(5) << rx
                  << " Y: " << std::setw(5) << ry << "    \n"
                  << "     Trigger: L-Trig: " << std::setw(5) << lTrig
                  << " R-Trig: " << std::setw(5) << rTrig << "    \n";
        std::cout << "  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n";
    }

    static void printControllersSection()
    {
        std::cout << "[CONNECTED CONTROLLERS]\n";
        int connectedCount = 0;
        int maxControllers = GLFW_JOYSTICK_LAST - GLFW_JOYSTICK_1 + 1;

        for (int jid = 0; jid < maxControllers; jid++)
        {
            if (isControllerPresent(jid))
            {
                connectedCount++;
                printSingleController(jid);
            }
        }

        if (connectedCount == 0)
        {
            std::cout << "  No controllers detected.                                              \n";
        }
    }

    // ========================================================================
    // ÖFFENTLICHE API-FUNKTION (Maximal optimierte Version)
    // ========================================================================
    void debugPrintAllInput()
    {
        std::cout << "\033[H"; // Cursor nach oben links setzen

        printLine('=');
        std::cout << "# " << std::string(LAYOUT.paddingLeft, ' ') << TITLE
                  << std::string(LAYOUT.paddingRight, ' ') << " #\n";
        printLine('=');

        // --- DIE UNTERBEREICHE ---
        printWindowSection();
        printLine('-');

        printKeyboardSection();
        printLine('-');

        printMouseSection();
        printLine('-');

        printControllersSection();
        printLine('=');
        std::cout << std::flush;
    }
}