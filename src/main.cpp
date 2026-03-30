#include <iostream>
#include <GLFW/glfw3.h>

int main(){
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(1280, 720, "opencraft", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}