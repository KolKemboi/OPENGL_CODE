#include "engine.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <utility>

#include "model.h"

Engine::Engine() : m_Width(640), m_Height(480) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(int hint, int value)
  this->m_Window = glfwCreateWindow(this->m_Width, this->m_Height,
                                    "Default Window", nullptr, nullptr);
  if (!this->m_Window) {
    std::cout << "WINDOW_ERROR" << std::endl;
    glfwTerminate();
  }
  glfwMakeContextCurrent(this->m_Window);
  gladLoadGL();
  glViewport(0, 0, this->m_Width, this->m_Height);
}

Engine::~Engine() {
  glfwDestroyWindow(this->m_Window);
  this->m_Window = nullptr;
  glfwTerminate();
}

void Engine::runEngine() {
  while (!glfwWindowShouldClose(this->m_Window)) {
    glClear(GL_COLOR_BUFFER_BIT);



    glClearColor(0.3, 0.1, 0.2, 1.0);
    closeWindow(this->m_Window);
    Model model;
    model.makeModel();
    model.renderModel();
    glfwPollEvents();
    
    glfwSwapBuffers(this->m_Window);
  }
}

void Engine::closeWindow(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
