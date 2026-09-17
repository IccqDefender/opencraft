#include "Game.h"

void Game::Start() {
    m_window = new Window();

    m_window->initialize();
    m_window->createCurrentWindow();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window->getCurrentWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");

    while (!m_window->isCurrentWindowShouldClose()) {
        Update();
    }
}

void Game::Update() {
    m_window->pollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Settings");
    ImGui::Text("Hello ImGUI!");
    ImGui::End();

    ImGui::Render();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    m_window->swapBuffers();
}

void Game::Stop() {

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
