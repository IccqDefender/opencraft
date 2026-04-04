#include "WindowManager.h"

WindowManager::WindowManager(){
    if(!glfwInit()){
        std::cout << "Failed to init GLFW!" << std::endl;
    }
}

WindowManager::~WindowManager(){
    glfwDestroyWindow(m_window.get());
    glfwTerminate();
}

void WindowManager::CreateWindow(uint32_t width, uint32_t height, const char* title){
    GLFWwindow* rawWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
    m_window.reset(rawWindow);
    glfwMakeContextCurrent(m_window.get());
}