#pragma once

#include <memory>
#ifndef GLAD_GUARD_
#include <glad/glad.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

class Camera {
public:
  Camera(std::shared_ptr<Shader> shader);
  void SetView();
  void SetProjection();
private:
  unsigned int shader;
  glm::mat4 m_View, m_Projection;
  unsigned int m_ViewLoc, m_ProjectionLoc;
};
