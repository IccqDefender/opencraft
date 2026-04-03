#include "WindowManager.h"

WindowManager::WindowManager(){
    glfwInit();
    if(!glfwInit()){
        std::cout << "Failed to init GLFW!" << std::endl;
    }
}

WindowManager::~WindowManager(){
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

WindowManager::CreateWindow(GLFWwindow* window, unsigned int width, unsigned int height, const char* title){
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(window)
}