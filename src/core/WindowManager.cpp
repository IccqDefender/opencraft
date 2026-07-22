#include "WindowManager.h"

#include <iostream>
#include <ostream>

int WindowManager::initializeWindowManager() {
    /* initialize GLFW */
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW!" << std::endl;
        return -1;
    }

    /* window hints */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    return 0;
}

void WindowManager::cleanupWindowManager(GLFWwindow* window) {
    /* cleanup window & GLFW */
    glfwDestroyWindow(window);
    glfwTerminate();
}

void WindowManager::createWindow(uint32_t width, uint32_t height, const char *title) {
    /* create GLFW window */
    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
    }

    /* show current window */
    glfwMakeContextCurrent(m_window);
#if defined(__linux__) // if platform is linux -> call this method (for wayland)
    glfwShowWindow(m_window);
#endif
}
