#pragma once
#include "../WindowManager/WindowManager.h"

class Engine{
public:
    Engine();
    ~Engine();

    void Run();
    void StartMainLoop();
    void Stop();

private:
    std::unique_ptr<WindowManager> _windowManager;
};