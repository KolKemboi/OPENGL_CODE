#pragma once

#include <memory>
#ifndef _GLAD_GUARD
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"

class Camera {
public:
	Camera(std::shared_ptr<Shader>shader, unsigned int width, unsigned int height);
	void setProjection();
	void setView();

private:
  // TODO:  implement the view, and the
	unsigned int e_Shader, e_Width, e_Height;
	glm::mat4 m_View, m_Projection;
	unsigned int m_ViewLoc, m_ProjectionLoc;
};
