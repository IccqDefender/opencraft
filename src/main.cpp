#include "core/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const char* vertexShaderSource = R"(
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 uProjection;

void main() {
  gl_Position = uProjection * vec4(aPos, 1.0);
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
    // position            // color
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // верх-право   - красный
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // низ-право    - зелёный
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // низ-лево     - синий
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f  // верх-лево    - жёлтый
    };

    uint32_t indices[] = {
      0, 1, 3,
      1, 2, 3
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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


      float aspect = 1280.0f / 720.0f;
      glm::mat4 projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);

      glUseProgram(shaderProgram);
      GLint projectionLoc = glGetUniformLocation(shaderProgram, "uProjection");
      glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      windowManager->swapBuffers();
      windowManager->pollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
  }
  
  return 0;
}
