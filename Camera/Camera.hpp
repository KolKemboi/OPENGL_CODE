#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Cam_Mov
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
};


const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;


class Camera
{
public:
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
		   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		GLfloat yaw = YAW, GLfloat pitch = PITCH): front(glm::vec3(0.0f, 0.0f, -1.0f)),
		movSpeed(SPEED), mouseSens(SENSITIVITY), zoom(ZOOM)
	{
		this->pos = pos;
		this->worldUp = up;
		this->yaw = yaw;
		this->pitch = pitch;
		this->updateCamVecs();
	}
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) :
		front(glm::vec3(0.0f, 0.0f, -1.0f)),
		movSpeed(SPEED), mouseSens(SENSITIVITY), zoom(ZOOM) 
	{
		this->pos = glm::vec3(posX, posY, posZ);
		this->worldUp = glm::vec3(upX, upY, upZ);
		this->yaw = yaw;
		this->pitch = pitch;
		this->updateCamVecs();
	}

	glm::mat4 GetViewMat()
	{
		return glm::lookAt(this->pos, this->pos + this->front, this->up);
	}

	void ProcessKeyboard(Cam_Mov direction, GLfloat deltaTime)
	{
		GLfloat velocity = this->movSpeed * deltaTime;
		if (FORWARD == direction)
		{
			this->pos += this->front * velocity;
		}
		if (BACKWARD == direction)
		{
			this->pos -= this->front * velocity;
		}
		if (LEFT == direction)
		{
			this->pos -= this->right * velocity;
		}
		if (RIGHT == direction)
		{
			this->pos += this->right * velocity;
		}
	}

	void ProcessMouseMov(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true)
	{
		xOffset *= this->mouseSens;
		yOffset *= this->mouseSens;

		this->yaw += xOffset;
		this->pitch += yOffset;

		if (constrainPitch)
		{
			if (this->pitch > 89.0f)
			{
				this->pitch = 89.0f;
			}
			if (this->pitch < -89.0f)
			{
				this->pitch = -89.0f;
			}
		}
		this->updateCamVecs();
	}
	void ProcessMouseScroll(GLfloat yOffset)
	{
		if (this->zoom >= 1.0f && this->zoom <= 45.0f)
		{
			this->zoom -= yOffset;
		}
		if (this->zoom <= 1.0f)
		{
			this->zoom = 1.0f;
		}
		if (this->zoom >= 45.0f)
		{
			this->zoom = 45.0f;
		}

	}
	GLfloat GetZoom()
	{
		return this->zoom;
	}

private:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;
	GLfloat movSpeed;
	GLfloat mouseSens;
	GLfloat zoom;

	void updateCamVecs()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		front.y = sin(glm::radians(this->pitch));
		front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)) ;
		
		this->front = glm::normalize(front);
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));

	}

};
