#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class WindowManager{
public:
    void Initialize();
    void CreateWindow(uint32_t width, uint32_t height, const char* title);
    GLFWwindow* GetCurrentWindow() { return m_window; }
    bool ShouldWindowClose() { return glfwWindowShouldClose(m_window); }

    void CleanUp();
private:
    GLFWwindow* m_window;
};