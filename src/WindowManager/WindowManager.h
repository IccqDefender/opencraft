#pragma once
#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>

class WindowManager{
public:
    WindowManager();
    ~WindowManager();

    GLFWwindow* GetWindow() { return m_window; }
    bool ShouldWindowClose() { return glfwWindowShouldClose(m_window); }

    void CreateWindow(uint32_t width, uint32_t height, const char* title);

private:
    GLFWwindow* m_window;
};