#pragma once

#ifndef GLAD_GUARD_
#include "glad/glad.h"
#endif // !GLAD_GUARD_
#include <GLFW/glfw3.h>
#include <iostream>

class Engine {
public:
  Engine();
  ~Engine();
  void runEngine();

private:
  void closeWindow(GLFWwindow *window);

private:
  unsigned int m_Width, m_Height;
  GLFWwindow *m_Window;
};
