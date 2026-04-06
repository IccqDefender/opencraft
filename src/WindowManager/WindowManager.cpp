#include "WindowManager.h"

WindowManager::WindowManager(){
    if(!glfwInit()){
        throw std::runtime_error("Failed to init GLFW!");
    }
}

WindowManager::~WindowManager(){
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void WindowManager::CreateWindow(uint32_t width, uint32_t height, const char* title){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if(!m_window){ throw std::runtime_error("Failed to create GLFW window!"); }
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGL()){ throw std::runtime_error("Failed to initialize GLAD!"); }
}