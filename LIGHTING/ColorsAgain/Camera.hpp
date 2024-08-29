#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"

class Camera
{
public:
	Camera();
	~Camera();

	glm::vec3 camPos = glm::vec3(0.0f, 1.0f, 3.5f);
private:
	glm::vec3 up;
	glm::vec3 front;

	int Sensitivity;
	int Speed;
};

Camera::Camera()
{
}

Camera::~Camera()
{
}
