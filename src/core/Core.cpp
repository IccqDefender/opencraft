#include "Core.h"

void Core::run() {
    /* initialize window manager */
    m_windowManager = std::make_unique<WindowManager>();
    m_windowManager->initializeWindowManager();

    m_windowManager->createWindow(WIDTH, HEIGHT, TITLE);

    /* update method */
    update();
}

void Core::stop() {
    /* cleanup */
    m_windowManager->cleanupWindowManager(m_windowManager->getCurrentWindow());
}

void Core::update() {
    /* infinity cycle */
    while (!(m_windowManager->isWindowShouldClose())) { // if window should close -> stop cycle
        // poll events
        m_windowManager->pollEvents();
        if (glfwGetKey(m_windowManager->getCurrentWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            m_windowManager->setWindowShouldClose(m_windowManager->getCurrentWindow()); // if ESC was pressed -> window should close
        }
        // TODO: swap buffers
        glfwSwapBuffers(m_windowManager->getCurrentWindow());
    }
}
