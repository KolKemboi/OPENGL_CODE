#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Camera
{
public:
	Camera();
	~Camera();
	void LookAround(GLFWwindow* window);
	void setCamVectors(Shader& shader);
	glm::vec3 camPos = glm::vec3(0.0f, 1.0f, 3.0f);
private:
	glm::vec3 up;
	glm::vec3 front;

	int Sensitivity = 50;
	int Speed;

	glm::mat4 view;
	glm::mat4 proj;
	float firstClick = true;
	GLint viewLoc;
	GLint projLoc;
	int width = 800, height = 800;
};

Camera::Camera()
{
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);

	this->view = glm::mat4(1.0f);
	this->proj = glm::mat4(1.0f);
}

Camera::~Camera()
{
}

void Camera::LookAround(GLFWwindow* window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		if (firstClick)
		{
			glfwSetCursorPos(window, (this->width / 2), (this->height / 2));
			firstClick = false;
		}
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = Sensitivity * (float)(mouseY - (this->height / 2)) / this->height;
		float rotY = Sensitivity * (float)(mouseX - (this->height / 2)) / this->height;
		glm::vec3 newFront = glm::rotate(this->front, glm::radians(-rotX), glm::normalize(glm::cross(this->front, this->up)));

		if (abs(glm::angle(newFront, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			this->front = newFront;
		}
		this->front = glm::rotate(this->front, glm::radians(-rotY), this->up);
		glfwSetCursorPos(window, (this->width / 2), (this->height / 2));

	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void Camera::setCamVectors(Shader& shader)
{
	this->view = glm::lookAt(this->camPos, this->camPos + this->front, this->up);
	this->proj = glm::perspective(45.0f, (GLfloat)1.0, 0.1f, 1000.0f);

	this->viewLoc = glGetUniformLocation(shader.ShaderProgram, "view");
	this->projLoc = glGetUniformLocation(shader.ShaderProgram, "proj");

	glUniformMatrix4fv(this->viewLoc, 1, GL_FALSE, glm::value_ptr(this->view));
	glUniformMatrix4fv(this->projLoc, 1, GL_FALSE, glm::value_ptr(this->proj));

}
