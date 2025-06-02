#pragma once

#ifndef GLAD_GUARD_
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include "model.h"

class Engine {
public:
  Engine();
  ~Engine();
  void runEngine() const;
  void closeWindow(GLFWwindow* window) const;
private:
  GLFWwindow* m_Window;
  std::unique_ptr<Model> m_Model;
  unsigned int m_Width, m_Height;
};
