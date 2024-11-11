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
	glm::vec3 pos;
	Camera();
	~Camera();
	void LookAround(GLFWwindow* window);
	void setCamera(Shader& shaderProg);
private:
	glm::mat4 view;
	glm::mat4 proj;
	glm::vec3 up;
	glm::vec3 front;
	GLint viewLoc, projLoc;
	float sensitivity;
	float speed;

	bool firstClick = true;
};

Camera::Camera():sensitivity(SENSITIVITY), speed(SPEED)
{
	this->pos = glm::vec3(0.0f, 1.0f, 3.5f);
	this->proj = glm::mat4(1.0f);
	this->view = glm::mat4(1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);

}
Camera::~Camera()
{

}

void Camera::LookAround(GLFWwindow* window)
{
}

void Camera::setCamera(Shader& shaderProg)
{
	this->view = glm::lookAt(this->pos, this->pos + this->front, this->up);
	this->proj = glm::perspective(45.0f, (GLfloat)1, 0.1f, 1000.0f);

	this->viewLoc = glGetUniformLocation(shaderProg.ShaderProgram, "view");
	this->projLoc = glGetUniformLocation(shaderProg.ShaderProgram, "proj");

	glUniformMatrix4fv(this->viewLoc, 1, GL_FALSE, glm::value_ptr(this->view));
	glUniformMatrix4fv(this->projLoc, 1, GL_FALSE, glm::value_ptr(this->proj));
}
