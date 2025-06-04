#include "camera.h"
#include "shader.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>
#include <memory>

Camera::Camera(std::shared_ptr<Shader> shader) {
  this->m_View = glm::mat4(1.0f);
  this->m_Projection = glm::mat4(1.0f);
  this->shader = shader->returnShader();

  this->m_ViewLoc = glGetUniformLocation(this->shader, "view");
  this->m_ProjectionLoc = glGetUniformLocation(this->shader, "projection");

}

void Camera::SetView(){
  this->m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  glUniformMatrix4fv(this->m_ViewLoc, 1, GL_FALSE, glm::value_ptr(this->m_View));
}

// TODO: Make sure to make the projection take in screen width and height automatically
void Camera::SetProjection(){
  this->m_Projection = glm::perspective(glm::radians(45.0f), 640.0f/480.0f, 0.1f, 100.0f);
  glUniformMatrix4fv(this->m_ProjectionLoc, 1, GL_FALSE, glm::value_ptr(this->m_Projection));

}
