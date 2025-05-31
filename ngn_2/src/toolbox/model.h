#pragma once

#include <vector>
#ifndef GLAD_GUARD_
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

class Model{
public:
  unsigned int m_vao;
  Model();
  void renderModel();
  void destroyModel();
private:
  std::vector<unsigned int> idxs;
  std::vector<float> verts;
  unsigned int m_vbo, m_ibo;
};
