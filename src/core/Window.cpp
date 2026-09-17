#include "Window.h"

#include <iostream>

// Initialize window
bool Window::initialize() {
    if (!glfwInit()) {
        std::cerr << "[FATAL] [GLFW] GLFW initialization failed!" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    std::cout << "[INFO] [GLFW] GLFW initialized!" << std::endl;
    return true;
}

bool Window::cleanup() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
    std::cout << "[INFO] [GLFW] GLFW destroyed!]" << std::endl;
    return true;
}

//Create window
bool Window::createCurrentWindow() {
    m_window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
    if (!m_window) {
        std::cerr << "[FATAL] [GLFW] Window creation failed!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "[INFO] [GLAD] Failed to initialize GLAD!" << std::endl;
        glfwDestroyWindow(m_window);
        glfwTerminate();
        return false;
    }

    std::cout << "[INFO] [GLFW] Window created!" << std::endl;
    return true;
}

void Window::pollEvents() {
    glfwPollEvents();
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        setCurrentWindowShouldClose();
    }
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_window);
}
