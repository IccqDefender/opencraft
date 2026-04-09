#include "Engine.h"
#include <GLFW/glfw3.h>

namespace opencraft {
    Engine::Engine(uint32_t width, uint32_t height, const char* title){
        _windowManager = new WindowManager();

        m_WINDOW_WIDTH = width;
        m_WINDOW_HEIGHT = height;
        m_WINDOW_TITLE = title;
    }

    Engine::~Engine(){

    }

    void Engine::Run(){
        _windowManager->CreateWindow(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, m_WINDOW_TITLE);

        StartMainLoop();
    }

    void Engine::StartMainLoop(){
        while(!_windowManager->IsShouldWindowClose()){
            glfwPollEvents();

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(_windowManager->GetWindow());
        }
    }

    void Engine::Stop(){
        //delete _imguiManager;
        //delete _windowManager;
    }
}