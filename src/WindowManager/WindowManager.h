#include <GLFW/glfw3.h>

class WindowManager{
public:
    WindowManager();
    ~WindowManager();

    GLFWwindow GetWindow() { return m_window; }
    bool ShouldWindowClose() { return glfwWindowShouldClose(m_window); }

    void CreateWindow(GLFWwindow* window);

private:
    GLFWwindow* m_window = nullptr;


};