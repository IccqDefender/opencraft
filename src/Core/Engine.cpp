#include "Engine.h"

Engine::Engine(){
    _windowManager = std::make_unique<WindowManager>();
}

Engine::~Engine(){

}

void Engine::Run(){
    _windowManager->CreateWindow(800, 600, "opengl");
    StartMainLoop();
}

void Engine::StartMainLoop(){
    while(!_windowManager->ShouldWindowClose()){
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(_windowManager->GetWindow());
    }    
}

void Engine::Stop(){

}