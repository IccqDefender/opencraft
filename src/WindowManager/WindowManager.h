#pragma once
#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>

class WindowManager{
public:
    WindowManager();
    ~WindowManager();

    GLFWwindow* GetWindow() { return m_window.get(); }
    bool ShouldWindowClose() { return glfwWindowShouldClose(m_window.get()); }

    void CreateWindow(uint32_t width, uint32_t height, const char* title);

private:
    std::unique_ptr<GLFWwindow> m_window = std::make_unique<GLFWwindow>();
};