#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "MeshLoader.h"
#include <iostream>

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
		: m_Pos(glm::vec3(0.0f, 1.0f, 3.5f)),
		m_Up(glm::vec3(0.0, 1.0, 0.0)),
		m_Right(glm::vec3(-1.0, 0.0, 0.0)),
		m_Yaw(-90.0f),
		m_Pitch(0.0f),
		m_Sensitivity(20.0f),
		m_Speed(10.0f),
		m_Projection(glm::mat4(1.0)),
		m_View(glm::mat4(1.0)),
		m_NearPlane(0.1f),
		m_FarPlane(100.0f)
	{
		this->updateCameraVectors();
	}

	void SetView(Mesh& mesh) 
	{
		this->m_View = glm::lookAt(this->m_Pos, this->m_Pos + this->m_Front, this->m_Up);
		glUniformMatrix4fv(glGetUniformLocation(mesh.m_Shader.retShader(), "view"), 1, GL_FALSE, glm::value_ptr(this->m_View));
	}

	void SetProjection(Mesh& mesh, u_int width, u_int height)
	{

		float aspectRatio = static_cast<float>(width) / height;

		this->m_Projection = glm::perspective(glm::radians(45.0f), aspectRatio, this->m_NearPlane, this->m_FarPlane);

		glUniformMatrix4fv(glGetUniformLocation(mesh.m_Shader.retShader(), "projection"), 1, GL_FALSE, glm::value_ptr(this->m_Projection));
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
	glm::vec3 m_Pos, m_Up, m_Right, m_Front;
	float m_Yaw, m_Pitch;

	float m_Sensitivity, m_Speed;

	glm::mat4 m_Projection, m_View;

	float m_NearPlane, m_FarPlane;
	
	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);

		// Recalculate the Right and Up vector
		m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
};
