#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"


class Camera
{
public:
	Camera()
	{
		this->m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		this->m_Pos = glm::vec3(0.0f, 3.5f, 2.0f);
		this->camFOV = 45.0f;
		this->m_NearPlane = 0.1f;
		this->m_FarPlane = 1000.0f;
		this->m_View = glm::mat4(1.0f);
		this->m_Projection = glm::mat4(1.0f);
	}
	void SetCamMatrices(Shader& shader)
	{
	}

private:
	glm::vec3 m_Up, m_Front, m_Pos;
	float m_NearPlane, m_FarPlane, camFOV;

	glm::mat4 m_View, m_Projection;
};
