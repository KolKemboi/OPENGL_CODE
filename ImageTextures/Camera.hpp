#pragma once

#include "Shader.hpp"
#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum Cam_movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 6.0f;
const float SENSITIVITY = 0.25f;
const float ZOOM = 45.0f;

class Camera
{
public:
    Camera(int width, int height);
    ~Camera();
    void setCamera(Shader& shader);
    void updateCamVecs();

    void ProcessKeyboard(Cam_movement dir, float deltaTime)
    {

    }

private:
    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 pos;
    glm::vec3 right;

    int width, height;

    float nearPlane, farPlane, camFOV, pitch, yaw, movementSpeed, mouseSens;

    glm::mat4 view, proj;

};

Camera::Camera(int width, int height)
    : width(width), height(height), camFOV(ZOOM), nearPlane(0.1f),
    farPlane(1000.0f),
    pos(glm::vec3(0.0f, 1.0f, 3.5f)), 
    front(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
    yaw(YAW), pitch(PITCH), movementSpeed(SPEED), mouseSens(SENSITIVITY)
{
    this->updateCamVecs();
}

Camera::~Camera()
{
}

void Camera::setCamera(Shader& shader)
{
    view = glm::lookAt(pos, pos + front, up);
    proj = glm::perspective(glm::radians(camFOV), (float)width / height, nearPlane, farPlane);

    int viewLoc = glGetUniformLocation(shader.ShaderProgram, "view");
    int projLoc = glGetUniformLocation(shader.ShaderProgram, "proj");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
}

void Camera::updateCamVecs()
{
    glm::vec3 front;
    front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    front.y = sin(glm::radians(this->pitch));
    front.x = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

    this->front = glm::normalize(front);

    this->right = glm::normalize(glm::cross(this->front, this->up));
    this->up = glm::normalize(glm::cross(this->right, this->front));

}