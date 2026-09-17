#ifndef OPENCRAFT_WINDOW_H
#define OPENCRAFT_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:

    bool initialize(); //Initialize window method
    bool cleanup(); //Cleanup window method

    bool createCurrentWindow(); //Create window method
    GLFWwindow* getCurrentWindow() { return m_window; }; //Get current window method
    bool isCurrentWindowShouldClose() { return glfwWindowShouldClose(m_window); }; //Is window should close method
    void setCurrentWindowShouldClose() { glfwSetWindowShouldClose(m_window, GLFW_TRUE); }; //Close window method

    void pollEvents();  //Poll events method
    void swapBuffers(); //Swap buffers method
private:
    const int WIDTH = 1280;             //Window width
    const int HEIGHT = 720;             //Window height
    const char* TITLE = "opencraft";    //Window title

    GLFWwindow* m_window = nullptr;     //Window pointer

};


#endif //OPENCRAFT_WINDOW_H
