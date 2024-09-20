#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

#include "Shader.h"

enum CameraMovement
{
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
	UP,
	DOWN,
};


class Camera
{
public:
	Camera(unsigned int width, unsigned int height)
	{
		this->width = width;
		this->height = height;
		this->updateCamVecs();
	}
	void setCamVecs(Shader& shader)
	{
		shader.UseShader();
		
		glm::mat4 projection = glm::perspective(this->FOV, (float)this->width/this->height, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(pos, pos + front, worldUp);
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

	}
	void lookAround(GLFWwindow* window)
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			if (this->firstclick)
			{
				glfwSetCursorPos(window, (this->width / 2), (this->height / 2));
				this->firstclick = false;
			}

			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			float rotX = this->sensitivity * (float)(mouseY - (this->height / 2)) / this->height;
			float rotY = this->sensitivity * (float)(mouseX - (this->height / 2)) / this->height;

			glm::vec3 newFront = glm::rotate(this->front, glm::radians(-rotX), glm::normalize(glm::cross(this->front, this->worldUp)));

			if (abs(glm::angle(newFront, this->worldUp) - glm::radians(90.0f)) <= glm::radians(85.0f))
			{
				this->front = newFront;
			}
			this->front = glm::rotate(this->front, glm::radians(-rotY), this->worldUp);
			glfwSetCursorPos(window, (this->width / 2), (this->height / 2));


		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			this->firstclick = true;
		}
	}

	void moveAround(CameraMovement dir, float deltaTime)
	{
		float velocity = speed * deltaTime;
		if (dir == FORWARD) this->pos += this->front * velocity;
		if (dir == BACKWARD) this->pos -= this->front * velocity;
		if (dir == LEFT) this->pos -= this->right * velocity;
		if (dir == RIGHT) this->pos += this->right * velocity;
		if (dir == UP) this->pos += this->worldUp * velocity;
		if (dir == DOWN) this->pos -= this->worldUp * velocity;
	}
private:
	glm::mat4 view, projection;
	GLFWwindow* window;
	int speed = 6, sensitivity = 50;
	unsigned int width, height;

	float FOV = 45.0f;
	float yaw = -90.0f;
	float pitch = 0.0f;
	glm::vec3 pos = glm::vec3(0.0f, 1.0f, 3.0f);
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3  front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	bool firstclick = true;

	void updateCamVecs()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		front.y = sin(glm::radians(this->pitch));
		front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));


		this->front = glm::normalize(front);

		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		
		this->worldUp = glm::normalize(glm::cross(this->right, this->front));
	}
};
