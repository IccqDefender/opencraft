#pragma once
#include "../WindowManager/WindowManager.h"
#include "WindowManager/ImguiManager/ImguiManager.h"
#include <memory>

class Engine{
public:
    Engine();
    ~Engine();

    void Run(uint32_t width, uint32_t height, const char* title);
    void StartMainLoop();
    void Stop();

private:
    std::unique_ptr<WindowManager> _windowManager;
    std::unique_ptr<ImguiManager> _imguiManager;

    uint32_t m_WINDOW_WIDTH;
    uint32_t m_WINDOW_HEIGHT;

    const char* m_WINDOW_TITLE;
};