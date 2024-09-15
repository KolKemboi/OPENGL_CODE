#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Shader.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

enum Cam_Movement
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
	Camera(int width, int height);
	~Camera();
	void LookAround(GLFWwindow* window);
	void MoveAround(Cam_Movement dir, float deltaTIme);
	void ScrollAction(float yOffset);
	void setCamVectors(Shader& shader);
	glm::vec3 camPos = glm::vec3(0.0f, 1.0f, 3.5f);
private:
	glm::vec3 up;
	glm::vec3 front;
	glm::mat4 view;
	glm::mat4 proj;
	glm::vec3 right;

	int width, height;
	GLint viewLoc;
	GLint projLoc;

	bool firstClick = true;
	
	float yaw = -90.0f, pitch = 0.0f, speed = 6.0f, sens = 50.0f, zoom = 45.0f;
};

Camera::Camera(int width, int height)
{
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->camPos = glm::vec3(0.0f, 1.0f, 3.5f);
	this->width = width;
	this->height = height;
	this->view = glm::mat4(1.0f);
	this->proj = glm::mat4(1.0f);
	this->right = glm::normalize(glm::cross(this->front, this->up));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

Camera::~Camera()
{
}

void Camera::LookAround(GLFWwindow* window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); // Hides the cursor
		//prevent snapping
		if (this->firstClick)
		{
			glfwSetCursorPos(window, (this->width / 2), (this->height / 2));
			this->firstClick = false;
		}
		//get mouse position
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		//creates rotation 
		float rotX = this->sens * (float)(mouseY - (this->height / 2)) / this->height;
		float rotY = this->sens * (float)(mouseX - (this->width  / 2)) / this->width;
		//prevents barrel roll
		glm::vec3 newFront = glm::rotate(this->front, glm::radians(-rotX), glm::normalize(glm::cross(this->front, this->up)));
		if (abs(glm::angle(newFront, this->up) - glm::radians(90.0f) <= glm::radians(85.0f)))
		{
			this->front = newFront;
		}
		//rotates the camera
		this->front = glm::rotate(this->front, glm::radians(-rotY), this->up);
		glfwSetCursorPos(window, (this->width / 2), (this->height / 2));


	}
	//returns things to normal
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		this->firstClick = true;
	}
}

void Camera::MoveAround(Cam_Movement dir, float deltaTime)
{
	float velocity = this->speed * deltaTime;

	if (dir == FORWARD) this->camPos += this->front * velocity;
	if (dir == BACKWARD) this->camPos -= this->front * velocity;
	if (dir == RIGHT) this->camPos += this->right * velocity;
	if (dir == LEFT) this->camPos -= this->right * velocity;
	if (dir == UP) this->camPos += this->up * velocity;
	if (dir == DOWN) this->camPos -= this->up * velocity;
}

void Camera::ScrollAction(float yOffset)
{
	float velocity = this->speed * 0.2-;
	if (yOffset > 0) this->camPos += this->front * velocity;
	if (yOffset < 0) this->camPos -= this->front * velocity;
}

void Camera::setCamVectors(Shader& shader)
{
	this->view = glm::lookAt(this->camPos, this->camPos + this->front, this->up);
	this->proj = glm::perspective(45.0f, (GLfloat)width/height, 0.1f, 1000.0f);

	this->viewLoc = glGetUniformLocation(shader.ShaderProgram, "view");
	this->projLoc = glGetUniformLocation(shader.ShaderProgram, "proj");

	glUniformMatrix4fv(this->viewLoc, 1, GL_FALSE, glm::value_ptr(this->view));
	glUniformMatrix4fv(this->projLoc, 1, GL_FALSE, glm::value_ptr(this->proj));

}
