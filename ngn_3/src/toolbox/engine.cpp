#include "engine.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include "model.h"

Engine::Engine() : m_Width(640), m_Height(480) {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->m_Window = glfwCreateWindow(this->m_Width, this->m_Height, "Window",
                                    nullptr, nullptr);
  if (!this->m_Window) {
    std::cerr << "ERROR::WINDOW_FAILURE" << std::endl;
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(this->m_Window);
  
  gladLoadGL();
  glViewport(0, 0, static_cast<GLsizei>(this->m_Width), static_cast<GLsizei>(this->m_Height));

  this->m_Model = std::make_unique<Model>();
}

Engine::~Engine(){
  this->m_Model->destroyModel();
  this->m_Model = 0;
  glfwDestroyWindow(this->m_Window);
  this->m_Window = 0;
  glfwTerminate();
}

void Engine::runEngine() const {
  while (!glfwWindowShouldClose(this->m_Window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2, 0.1, 0.3, 1.0);

    this->m_Model->renderModel();
    closeWindow(this->m_Window);

    glfwSwapBuffers(this->m_Window);
    glfwPollEvents();
  }
}
void Engine::closeWindow(GLFWwindow* window) const {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}
