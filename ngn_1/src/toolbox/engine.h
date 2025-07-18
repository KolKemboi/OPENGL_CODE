#pragma once

#include <memory>
#ifndef GLAD_GUARD_
#include "glad/glad.h"
#endif // !GLAD_GUARD_
#include <GLFW/glfw3.h>
#include <iostream>
#include "model.h"

class Engine {
public:
  Engine();
  ~Engine();
  void runEngin();

private:
  void closeWindow(GLFWwindow *window);

private:
  unsigned int m_Width, m_Height;
  GLFWwindow *m_Window;
  std::shared_ptr<Model> m_Model;
};
