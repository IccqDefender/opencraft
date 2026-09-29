#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/Window.h"
#include "core/Input.h"

#include "render/Shader.h"
#include "render/Camera.h"
#include "render/Vertex.h"
#include "render/Mesh.h"

#include "world/Chunk.h"
#include "world/BlockRegistry.h"

int main() {
  std::unique_ptr<Window> windowManager = std::make_unique<Window>(1280, 720, "opencraft");
  std::unique_ptr<Camera> camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

  float lastFrame = 0.0f;

  try{
    windowManager->makeContextCurrent();

    Input::setCursorMode(windowManager->getWindow(), GLFW_CURSOR_DISABLED);

    Shader shader = Shader::fromFiles("../assets/shaders/shader.vert", "../assets/shaders/shader.frag");

    BlockRegistry::initialize();

    Chunk chunk(glm::ivec3(0, 0, 0));

    for (int x = 0; x < Chunk::SIZE_X; ++x){
      for (int z = 0; z < Chunk::SIZE_Z; ++z){
        for (int y = 0; y < 16; ++y){
          chunk.setBlock(x, y, z, BlockType::Stone);
        }

        chunk.setBlock(x, 15, z, BlockType::Dirt);
        chunk.setBlock(x, 16, z, BlockType::Grass);
      }
    }

    chunk.generateMesh();

    while (!windowManager->isWindowShouldClose()) {
      Input::update();
      windowManager->pollEvents();

      float currentFrame = static_cast<float>(glfwGetTime());
      float deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      if(Input::isKeyJustPressed(GLFW_KEY_ESCAPE)){
        windowManager->setWindowShouldClose(true);
      }

      camera->update(deltaTime);

      glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      float aspect = 1280.0f / 720.0f;

      shader.use();
      shader.setMat4("uView", camera->getViewMatrix());
      shader.setMat4("uProjection", camera->getProjectionMatrix(aspect));

      chunk.draw(shader);
      
      windowManager->swapBuffers();
    }

  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
  }
  
  return 0;
}
