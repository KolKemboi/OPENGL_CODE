#include "engine.h"
#include "model.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <memory>

Engine::Engine() : m_Height(480), m_Width(640) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->m_Window = glfwCreateWindow(this->m_Width, this->m_Height,
                                    "basic window", nullptr, nullptr);

  if (!this->m_Window) {
    std::cerr << "ERROR::WINDOW_FAILED::EXIT CODE 1" << std::endl;
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(this->m_Window);

  if (!gladLoadGL()) {
    std::cerr << "FAILED:: GLAD" << std::endl;
    glfwTerminate();
    return;
  }
  glViewport(0, 0, static_cast<GLsizei>(this->m_Width),
             static_cast<GLsizei>(this->m_Height));
  glEnable(GL_DEPTH_BUFFER_BIT);
  this->m_Model = std::make_shared<Model>();

  this->m_Model->makeModel();
}

// NOTE: destroy engine
Engine::~Engine() {
  glfwDestroyWindow(this->m_Window);
  this->m_Window = nullptr;
  glfwTerminate();
}

// NOTE: this is the runn engine
void Engine::runEngin() {
  while (!glfwWindowShouldClose(this->m_Window)) {
    glClearColor(0.3, 0.1, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    closeWindow(this->m_Window);

    this->m_Model->renderModel();

    glfwSwapBuffers(this->m_Window);
    glfwPollEvents();
  }
}

// NOTE: close window
void Engine::closeWindow(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
