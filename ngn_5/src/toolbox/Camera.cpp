#include "Camera.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>
#include <memory>

Camera::Camera(std::shared_ptr<Shader> shader, unsigned int width,
               unsigned int height) {
  e_Shader = shader->retShader();
  e_Height = height;
  e_Width = width;

  m_View = glm::mat4(1.0f);
  m_Projection = glm::mat4(1.0f);

  m_ViewLoc = glGetUniformLocation(e_Shader, "view");
  m_ProjectionLoc = glGetUniformLocation(e_Shader, "projection");
}

void Camera::setView() {
  m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  glUniformMatrix4fv(m_ViewLoc, 1, GL_FALSE, glm::value_ptr(m_View));
}

void Camera::setProjection() {
  m_Projection =
      glm::perspective(glm::radians(45.0f),
                       static_cast<float>(e_Width) / e_Height, 0.01f, 100.0f);
  glUniformMatrix4fv(m_ProjectionLoc, 1, GL_FALSE,
                     glm::value_ptr(m_Projection));
}
