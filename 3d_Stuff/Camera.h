#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Shader.h"

typedef unsigned int u_int;

enum Direction
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

class Camera
{
public:
	Camera()
	{

	}
	
	void SetView() const
	{

	}
	void SetProjection(u_int width, u_int height) const
	{

	}


	void MoveAround(Direction dir, float deltaTime)
	{

	}

	void LookAround(float deltaTime)
	{

	}

	void ZoomAround(float offset, float deltaTime)
	{

	}

private:
	glm::vec3 m_Pos = glm::vec3(0.0, 3.5, -2.0), m_Up = glm::vec3(0.0, 1.0, 0.0), m_Right = glm::vec3(-1.0, 0.0, 0.0);
	float m_Yaw = -90.0, m_Pitch = 0.0;

	float sensitivity = 20.0, speed = 10.0;
};
