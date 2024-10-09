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
	void SetCamMatrices()
	{

	}

private:
	glm::vec3 m_Up, m_Front, m_Pos;
	float m_NearPlane, m_FarPlane, camFOV;
};
