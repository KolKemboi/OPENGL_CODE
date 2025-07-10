#include "Engine.hpp"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <memory>

Engine::Engine() : m_Height(480), m_Width(640) {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->m_Window = glfwCreateWindow(this->m_Width, this->m_Height, "Window",
                                    nullptr, nullptr);

  if (!this->m_Window) {
    std::cerr << "WINDOW_CREATION_FAILED" << std::endl;
    glfwTerminate();
  }
  glfwMakeContextCurrent(this->m_Window);

  gladLoadGL();
  glViewport(0, 0, this->m_Width, this->m_Height);

  glEnable(GL_DEPTH_BUFFER_BIT);

  this->m_Model = std::make_shared<Model>();
}

Engine::~Engine() {
  this->m_Model->DestroyModel();
  glfwDestroyWindow(this->m_Window);
  this->m_Height = 0;
  this->m_Width = 0;
  this->m_Window = nullptr;
}

void Engine::runEngine() {
  while (!glfwWindowShouldClose(this->m_Window)) {
    this->closeWindow(this->m_Window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.1f, 0.3f, 1.0f);

    this->m_Model->renderModel();
    glfwSwapBuffers(this->m_Window);
    glfwPollEvents();
  }
}

void Engine::closeWindow(GLFWwindow *window) {

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
