#include "ImguiManager.h"

ImguiManager::ImguiManager() {
}

ImguiManager::~ImguiManager() {
    DestroyImGui();
}

void ImguiManager::CreateNewFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImguiManager::CreateUI() {
    ImGui::Begin("Hello, ImGui!");
    ImGui::Text("This is a simple ImGui window.");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / m_io.Framerate, m_io.Framerate);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiManager::InitImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void ImguiManager::DestroyImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
