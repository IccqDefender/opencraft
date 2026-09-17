#ifndef OPENCRAFT_GAME_H
#define OPENCRAFT_GAME_H

#include "../core/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Window;

class Game {
public:
    void Start();
    void Update();
    void Stop();

private:
    Window* m_window;
};


#endif //OPENCRAFT_GAME_H
