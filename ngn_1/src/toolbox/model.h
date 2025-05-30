#pragma once
#include <memory>
#ifndef GLAD_GUARD_
#include "glad/glad.h"
#endif // !GLAD_GUARD_
#include <vector>
#include "shader.h"

class Model {
public:
  unsigned int m_vao;

  void makeModel();
  void renderModel();
  void destroyModel();

private:
  unsigned int m_vbo, m_ibo;
  std::vector<float> verts;
  std::vector<unsigned int> idxs;
  std::shared_ptr<Shader> m_Shader;
};

