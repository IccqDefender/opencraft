#include "windowManager.h"

void WindowManager::Initialize()
{
    if (!glfwInit()){
        std::cerr << "Failed to init GLFW!\n";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void WindowManager::CreateWindow(uint32_t width, uint32_t height, const char* title)
{
    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_window){
        std::cerr << "Failed to create window!\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to initialize GLAD!\n";
        CleanUp();
    }

    glfwShowWindow(m_window);
}

void WindowManager::CleanUp()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
