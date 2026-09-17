#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "game/Game.h"

#include <iostream>

int main() {

    Game* m_game = new Game();

    m_game->Start();

    m_game->Stop();

    delete m_game;

    return 0;
}