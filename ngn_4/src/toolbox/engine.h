#pragma once

#include <memory>
#ifndef GLAD_GUARD_
#include <glad/glad.h>
#endif 
#include <GLFW/glfw3.h>
#include "model.h"

class Engine {
public:
  Engine();
  void runEngine();
  ~Engine();
private:
  void closeWindow(GLFWwindow* window);
private:
  std::unique_ptr<Model> m_Model;
  GLFWwindow* m_Window;
  unsigned int m_Width, m_Height;
};
