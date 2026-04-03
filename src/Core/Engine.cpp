#include "Engine.h"

Engine::Engine(){
    _windowManager = new WindowManager();
}

Engine::~Engine(){

}

void Engine::Run(){
    _windowManager->CreateWindow(_windowManager->GetWindow(), 800, 600, "opengl");
    StartMainLoop();
}

void Engine::StartMainLoop(){
    while(!_windowManager->ShouldWindowClose()){
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers();
    }    
}

void Engine::Stop(){
    delete _windowManager;
}