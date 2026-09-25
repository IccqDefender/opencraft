#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdint.h>
#include <stdexcept>

class Window {
public:
    Window(uint32_t width, uint32_t height, const char* title);
    ~Window();

    GLFWwindow* getWindow() const { return m_window; };

    void makeContextCurrent();

    void swapBuffers();
    void pollEvents();

    bool isWindowShouldClose() const { return glfwWindowShouldClose(m_window); };
    void setWindowShouldClose(bool flag) { glfwSetWindowShouldClose(m_window, flag); };

private:
    GLFWwindow* m_window;
};

#endif // WINDOW_H