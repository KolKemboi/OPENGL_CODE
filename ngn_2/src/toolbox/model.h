#pragma once

#include <memory>
#include <vector>
#ifndef GLAD_GUARD_
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Model{
public:
  unsigned int m_vao;
  Model();
  void SetModelLoc() const;
  void renderModel();
  void destroyModel();
private:
  std::vector<unsigned int> idxs;
  std::vector<float> verts;
  unsigned int m_vbo, m_ibo;
  std::unique_ptr<Shader> m_Shader;
  glm::mat4 m_Model;
  unsigned int m_ModelLoc;
};
