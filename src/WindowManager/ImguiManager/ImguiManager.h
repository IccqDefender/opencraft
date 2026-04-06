#ifndef OPENCRAFT_IMGUIMANAGER_H
#define OPENCRAFT_IMGUIMANAGER_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class ImguiManager {
public:
    ImguiManager();
    ~ImguiManager();

    void InitImGui(GLFWwindow* window);
    void CreateNewFrame();
    void CreateUI();
private:
    ImGuiIO& m_io = ImGui::GetIO();

    void DestroyImGui();
};


#endif //OPENCRAFT_IMGUIMANAGER_H