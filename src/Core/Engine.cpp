#include "Engine.h"
#include <GLFW/glfw3.h>

Engine::Engine(){
    _windowManager = std::make_unique<WindowManager>();
    _imguiManager = std::make_unique<ImguiManager>();
}

Engine::~Engine(){

}

void Engine::Run(uint32_t width, uint32_t height, const char* title){
    m_WINDOW_WIDTH = width;
    m_WINDOW_HEIGHT = height;
    m_WINDOW_TITLE = title;

    _windowManager->CreateWindow(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, m_WINDOW_TITLE);

    _imguiManager->InitImGui(_windowManager->GetWindow());

    StartMainLoop();
}

void Engine::StartMainLoop(){
    while(!_windowManager->ShouldWindowClose()){
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        _imguiManager->CreateNewFrame();
        _imguiManager->CreateUI();

        glfwSwapBuffers(_windowManager->GetWindow());
    }    
}

void Engine::Stop(){

}