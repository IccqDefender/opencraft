#include "engine.h"

Engine::Engine()
{
    m_windowManager = std::make_unique<WindowManager>();
}

void Engine::Start()
{
    m_windowManager->Initialize();
    m_windowManager->CreateWindow(800, 600, "opencraft");

    while(!m_windowManager->ShouldWindowClose()){
        Update();
    }
}

void Engine::Update()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(m_windowManager->GetCurrentWindow());
    glfwPollEvents();
}

void Engine::Stop()
{
    m_windowManager->CleanUp();
}
