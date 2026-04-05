#include "WindowManager.h"

WindowManager::WindowManager(){
    if(!glfwInit()){
        std::cout << "Failed to init GLFW!" << std::endl;
    }
}

WindowManager::~WindowManager(){
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void WindowManager::CreateWindow(uint32_t width, uint32_t height, const char* title){
    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
}