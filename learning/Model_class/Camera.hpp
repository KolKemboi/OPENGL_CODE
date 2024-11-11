#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
	glm::vec3 camPos = glm::vec3(0.0f, 1.0f, 3.5f);
private:
	glm::vec3 up;
	glm::vec3 front;

	int Sensitivity;
	int Speed;

	glm::mat4 view;
	glm::mat4 proj;

	GLint viewLoc;
	GLint projLoc;
};

Camera::Camera()
{
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->camPos = glm::vec3(0.0f, 1.0f, 3.5f);

	this->view = glm::mat4(1.0f);
	this->proj = glm::mat4(1.0f);
}

Camera::~Camera()
{
}

void Camera::LookAround(GLFWwindow* window)
{
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
