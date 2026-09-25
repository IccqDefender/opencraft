#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <glm/glm.hpp>

class Input {
public:
    static void initialize(GLFWwindow* window);

    static void update();

    static bool isKeyPressed(int key);
    static bool isKeyJustPressed(int key);
    static bool isKeyJustReleased(int key);

    static bool isMouseButtonPressed(int button);
    static bool isMouseButtonJustPressed(int button);
    static bool isMouseButtonJustReleased(int button);

    static glm::vec2 getMousePosition();
    static glm::vec2 getMouseDelta();

    static float getScrollDelta();
    
    static void setCursorMode(GLFWwindow* window, int mode);

private:
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    static std::unordered_map<int, bool> s_keysPressed;
    static std::unordered_map<int, bool> s_keysJustPressed;
    static std::unordered_map<int, bool> s_keysJustReleased;

    static std::unordered_map<int, bool> s_mouseButtonsPressed;
    static std::unordered_map<int, bool> s_mouseButtonsJustPressed;
    static std::unordered_map<int, bool> s_mouseButtonsJustReleased;

    static glm::vec2 s_mousePosition;
    static glm::vec2 s_lastMousePosition;
    static glm::vec2 s_mouseDelta;
    static bool s_firstMouseMovement;

    static float s_scrollDelta;
};

#endif // INPUT_H