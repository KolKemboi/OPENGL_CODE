#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.hpp"

float SPEED = 0.1f;
float SENSITIVITY = 100.0f;


class Camera
{
public:
	Camera() ;
	~Camera();
	void LookAround(GLFWwindow* window);
	void setCamera(Shader& shaderProg);
private:
	glm::mat4 view;
	glm::mat4 proj;
	glm::vec3 up;
	glm::vec3 front;
	glm::vec3 pos;
	GLint viewLoc, projLoc;
	float sensitivity;
	float speed;

	bool firstClick = true;
};

Camera::Camera() :speed(SPEED), sensitivity(SENSITIVITY)
{
	this->view = glm::mat4(1.0f);
	this->proj = glm::mat4(1.0f);

	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->pos = glm::vec3(0.0f, 1.0f, 3.5f);
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
			glfwSetCursorPos(window, (double)(800 / 2), (double)(800 / 2));
			firstClick = false;
		}
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		//TO-DO:: replace the 800  with height
		float rotX = this->sensitivity * (float)(mouseY - (800 / 2)) / 800;
		float rotY = this->sensitivity * (float)(mouseX - (800 / 2)) / 800;

		glm::vec3 newFront = glm::rotate(this->front, glm::radians(-rotX), glm::normalize(glm::cross(this->front, this->up)));

		if (!((glm::angle(newFront, this->up) <= glm::radians(5.0f)) or
			(glm::angle(newFront, -this->up) <= glm::radians(5.0f)))) {
			this->front = newFront;
		}

		this->front = glm::rotate(this->front, glm::radians(-rotY), this->up);

		glfwSetCursorPos(window, (800 / 2), (800 / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		this->firstClick = true;
	}

}

void Camera::setCamera(Shader& shaderProg)
{
	//TO-DO:: set the width and height dynamically
	proj = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)800, .01f, 100.0f);
	view = glm::lookAt(pos, pos + front, up);
	this->viewLoc = glGetUniformLocation(shaderProg.ShaderProgram, "view");
	this->projLoc = glGetUniformLocation(shaderProg.ShaderProgram, "proj");
	glUniformMatrix4fv(this->viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(this->projLoc, 1, GL_FALSE, glm::value_ptr(proj));

}
