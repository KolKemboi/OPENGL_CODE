#include "Shader.hpp"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
public:
	Camera(int width, int height);
	~Camera();
	void setCamera(Shader& shader);
private:
	glm::vec3 up;
	glm::vec3 front;
	glm::vec3 pos;

	int width, height;

	int viewLoc, projLoc;
	float nearPlane, farPlane, camFOV;

	glm::mat4 view, proj;

};

Camera::Camera(int width, int height)
{
	this->pos = glm::vec3(0.0f, 1.0f, 3.5f);
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->width = width;
	this->height = height;
	this->camFOV = 45.0f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.0f;
}

Camera::~Camera()
{
}

void Camera::setCamera(Shader& shader)
{
	this->view = glm::lookAt(this->pos, this->pos + this->front, this->up);
	this->proj = glm::perspective(45.0f, (float)width / height, this->nearPlane, this->farPlane);

	this->viewLoc = glGetUniformLocation(shader.ShaderProgram, "view");
	this->projLoc = glGetUniformLocation(shader.ShaderProgram, "proj");

	glUniformMatrix4fv(this->viewLoc, 1, GL_FALSE, glm::value_ptr(this->view));
	glUniformMatrix4fv(this->projLoc, 1, GL_FALSE, glm::value_ptr(this->proj));
}
