#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window/windowManager.h"

#include <memory>
#include <vector>


class Engine{
public:
    Engine();
    void Start();
    void Update();
    void Stop();
private:
    std::unique_ptr<WindowManager> m_windowManager;


};