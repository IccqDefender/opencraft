#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(){

  if (!glfwInit()){
    std::cerr << "Failed to init GLFW\n";
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "opencraft", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create window!\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cerr << "Failed to initialize GLAD!\n";
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  glfwShowWindow(window);

  while (!glfwWindowShouldClose(window)){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}