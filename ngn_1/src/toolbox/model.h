#pragma once
#ifndef GLAD_GUARD_
#include "glad/glad.h"
#endif // !GLAD_GUARD_
#include <vector>

class Model {
public:
  unsigned int m_vao;

  void makeModel();
  void renderModel();

private:
  unsigned int m_vbo, m_ibo;
  std::vector<float> verts;
  std::vector<unsigned int> idxs;
};
