#ifndef WINDOW_H
#define WINDOW_H

#include <stdint.h>
#include <stdexcept>

class GLFWwindow;

class Window {
public:
    Window(uint32_t width, uint32_t height, const char* title);
    ~Window();

    GLFWwindow* getWindow() const { return m_window; };

    void makeContextCurrent();

    void swapBuffers();
    void pollEvents();

    bool isWindowShouldClose();
    void setWindowShouldClose(bool flag);

private:
    GLFWwindow* m_window;
};

#endif // WINDOW_H