#ifndef OPENCRAFT_WINDOWMANAGER_H
#define OPENCRAFT_WINDOWMANAGER_H

#include "GLFW/glfw3.h"

class WindowManager {
public:
    /* Window manager methods*/
    int initializeWindowManager();                   // initialize window manager
    void cleanupWindowManager(GLFWwindow* window);   // cleanup window manager
private:
    /* Window manager variables*/
    GLFWwindow* m_window = nullptr;                  // current window
public:
    /* Current window methods */
    void createWindow(uint32_t width, uint32_t height, const char* title);                               // create current window
    bool isWindowShouldClose() { return glfwWindowShouldClose(m_window); };                              // is current window should close?
    void setWindowShouldClose(GLFWwindow* window) { glfwSetWindowShouldClose(window, GLFW_TRUE); }; // set current window should close
    GLFWwindow *getCurrentWindow() { return m_window; }; // get current window

    void pollEvents() { glfwPollEvents(); };                                                             // poll events method
};


#endif //OPENCRAFT_WINDOWMANAGER_H
