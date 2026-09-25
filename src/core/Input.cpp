#include "Input.h"

/*

    STATIC MEMBER VARIABLES

*/
std::unordered_map<int, bool> Input::s_keysPressed;
std::unordered_map<int, bool> Input::s_keysJustPressed;
std::unordered_map<int, bool> Input::s_keysJustReleased;

std::unordered_map<int, bool> Input::s_mouseButtonsPressed;
std::unordered_map<int, bool> Input::s_mouseButtonsJustPressed;
std::unordered_map<int, bool> Input::s_mouseButtonsJustReleased;

glm::vec2 Input::s_mousePosition = glm::vec2(0.0f, 0.0f);
glm::vec2 Input::s_lastMousePosition = glm::vec2(0.0f, 0.0f);
glm::vec2 Input::s_mouseDelta = glm::vec2(0.0f, 0.0f);
bool Input::s_firstMouseMovement = true;

float Input::s_scrollDelta = 0.0f;


/*

    INITIALIZATION

*/
void Input::initialize(GLFWwindow* window) {
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);
}

/*

    UPDATE

*/
void Input::update() {
    s_keysJustPressed.clear();
    s_keysJustReleased.clear();
    s_mouseButtonsJustPressed.clear();
    s_mouseButtonsJustReleased.clear();

    s_mouseDelta = glm::vec2(0.0f);

    s_scrollDelta = 0.0f;
}

/*

    KEYBOARD INPUT

*/
bool Input::isKeyPressed(int key){
    auto it = s_keysPressed.find(key);
    return it != s_keysPressed.end() && it->second;
}

bool Input::isKeyJustPressed(int key){
    auto it = s_keysJustPressed.find(key);
    return it != s_keysJustPressed.end() && it->second;
}

bool Input::isKeyJustReleased(int key){
    auto it = s_keysJustReleased.find(key);
    return it != s_keysJustReleased.end() && it->second;
}

/*

    MOUSE INPUT

*/
bool Input::isMouseButtonPressed(int button){
    auto it = s_mouseButtonsPressed.find(button);
    return it != s_mouseButtonsPressed.end() && it->second;
}

bool Input::isMouseButtonJustPressed(int button){
    auto it = s_mouseButtonsJustPressed.find(button);
    return it != s_mouseButtonsJustPressed.end() && it->second;
}

bool Input::isMouseButtonJustReleased(int button){
    auto it = s_mouseButtonsJustReleased.find(button);
    return it != s_mouseButtonsJustReleased.end() && it->second;
}

/*

    MOUSE POSITION AND SCROLL

*/
glm::vec2 Input::getMousePosition(){
    return s_mousePosition;
}

glm::vec2 Input::getMouseDelta(){
    return s_mouseDelta;
}

float Input::getScrollDelta(){
    return s_scrollDelta;
}

/*

    CURSOR MODE

*/
void Input::setCursorMode(GLFWwindow* window, int mode){
    glfwSetInputMode(window, GLFW_CURSOR, mode);
}

/*

    CALLBACKS

*/
void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        s_keysPressed[key] = true;
        s_keysJustPressed[key] = true;
    } else if (action == GLFW_RELEASE) {
        s_keysPressed[key] = false;
        s_keysJustReleased[key] = true;
    }
}

void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        s_mouseButtonsPressed[button] = true;
        s_mouseButtonsJustPressed[button] = true;
    } else if (action == GLFW_RELEASE) {
        s_mouseButtonsPressed[button] = false;
        s_mouseButtonsJustReleased[button] = true;
    }
}

void Input::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    glm::vec2 newPos((float)xpos, (float)ypos);

    if(s_firstMouseMovement){
        s_lastMousePosition = newPos;
        s_firstMouseMovement = false;
    }

    s_mouseDelta = newPos - s_lastMousePosition;
    s_lastMousePosition = newPos;
    s_mousePosition = newPos;
}

void Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    s_scrollDelta = (float)yoffset;
}