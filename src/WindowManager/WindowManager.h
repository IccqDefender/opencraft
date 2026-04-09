#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

namespace opencraft {
    class WindowManager{
    public:
        WindowManager();
        ~WindowManager();

        GLFWwindow* GetWindow() { return m_window; }
        bool IsShouldWindowClose() { return glfwWindowShouldClose(m_window); }

        void CreateWindow(uint32_t width, uint32_t height, const char* title);

    private:
        GLFWwindow* m_window;
    };
}