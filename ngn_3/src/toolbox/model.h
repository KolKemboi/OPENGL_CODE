#pragma once

#include <vector>
#ifndef GLAD_GUARD_
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Model {
public:
  Model();
  void renderModel() const;
  void destroyModel() ;
  void setModelLoc() ;
  unsigned int m_Vao;

private:
  unsigned int m_Vbo, m_Ibo;
  std::vector<float> m_Verts;
  std::vector<unsigned int> m_Idxs;
  glm::mat4 m_ModelUniform;
  unsigned int m_ModelLoc;
};
