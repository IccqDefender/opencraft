#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window(uint32_t width, uint32_t height, const char* title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    glfwWindowHintString(GLFW_WAYLAND_APP_ID, "opencraft");

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (m_window == nullptr) {
        throw std::runtime_error("Failed to create GLFW window\n");
    }
}

Window::~Window(){
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::makeContextCurrent()
{
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD\n");
    }

    glViewport(0, 0, 1280, 720);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_window);
}

void Window::pollEvents()
{
    glfwPollEvents();
    if (GLFW_KEY_ESCAPE == glfwGetKey(m_window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(m_window, true);
    }
}

bool Window::isWindowShouldClose()
{
    return glfwWindowShouldClose(m_window);
}

void Window::setWindowShouldClose(bool flag)
{
    glfwSetWindowShouldClose(m_window, flag);
}
