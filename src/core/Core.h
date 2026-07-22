#ifndef OPENCRAFT_CORE_H
#define OPENCRAFT_CORE_H

/* include opengl */
#include "glad/glad.h"
#include "GLFW/glfw3.h"

/* include managers */
#include "WindowManager.h"

/* include c++ libs */
#include <memory>

class Core {
public:
    void run();                                          // run core
    void stop();                                         // stop core
private:
    void update();                                       // update method
private:
    constexpr static int WIDTH = 1280;                          // setup window width
    constexpr static int HEIGHT = 720;                          // setup window height
    const char* TITLE = "opencraft";                            // setup window title

    std::unique_ptr<WindowManager> m_windowManager = nullptr;   // obj window manager class
};


#endif //OPENCRAFT_CORE_H
