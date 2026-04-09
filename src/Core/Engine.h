#pragma once
#include "../WindowManager/WindowManager.h"
#include <memory>

namespace opencraft {
    class Engine{
    public:
        Engine(uint32_t width, uint32_t height, const char* title);
        ~Engine();

        void Run();
        void StartMainLoop();
        void Stop();

    private:
        WindowManager*  _windowManager = nullptr;

        uint32_t m_WINDOW_WIDTH;
        uint32_t m_WINDOW_HEIGHT;

        const char* m_WINDOW_TITLE;
    };
}