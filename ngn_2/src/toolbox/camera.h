#pragma once

#ifndef GLAD_GUARD_
#include <glad/glad.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
  void SetView() const;
  void SetProjection() const;
private:
  glm::mat4 m_View, m_Projection;
  unsigned int m_ViewLoc, m_ProjectionLoc;
};
