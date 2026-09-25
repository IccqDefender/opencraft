#include "core/Window.h"

#include <iostream>
#include <stdexcept>

#include <memory>

const char* vertexShaderSource = R"(
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;
void main() {
  gl_Position = vec4(aPos, 1.0);
  ourColor = aColor;
}
)";

const char* fragmentShaderSource = R"(
#version 460 core
in vec3 ourColor;
out vec4 FragColor;
void main() {
  FragColor = vec4(ourColor, 1.0);
}
)";

GLuint compileShader(GLenum shaderType, const char* source) {
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    throw std::runtime_error("Shader compilation failed");
  }
  return shader;
}

GLuint createShaderProgram(){
  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
  GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    throw std::runtime_error("Shader program linking failed");
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}

int main() {
  std::unique_ptr<Window> windowManager = std::make_unique<Window>(1280, 720, "opencraft");

  try{
    windowManager->makeContextCurrent();

    float vertices[] = {
      //position          //color
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 
       0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
       0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint shaderProgram = createShaderProgram();

    while (!windowManager->isWindowShouldClose()) {
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      windowManager->swapBuffers();
      windowManager->pollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
  }
  
  return 0;
}
