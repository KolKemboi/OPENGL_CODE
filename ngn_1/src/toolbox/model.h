#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>
#ifndef GLAD_GUARD_
#include "glad/glad.h"
#endif // !GLAD_GUARD_
#include <vector>
#include "shader.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
  #include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Model {
public:
  unsigned int m_vao;

  void makeModel();
  void renderModel();
  void destroyModel();
  glm::mat4 view = glm::mat4(1.0f);

  glm::mat4 projection;
  glm::mat4 model = glm::mat4(1.0f);

private:
  unsigned int m_vbo, m_ibo;
  std::vector<float> verts;
  std::vector<unsigned int> idxs;
  std::shared_ptr<Shader> m_Shader;
};

