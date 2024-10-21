#pragma once

#include "Shader.hpp"
#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

enum Cam_movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 6.0f;
const float SENSITIVITY = 50.0f;
const float ZOOM = 45.0f;

class Camera
{
public:
    Camera(int width, int height);
    ~Camera();
    void setCamera(Shader& shader);

    void ProcessKeyboard(Cam_movement dir, float deltaTime)
    {
        float velocity = this->movementSpeed * deltaTime;

        if (dir == FORWARD) this->pos += this->front * velocity;
        if (dir == BACKWARD) this->pos -= this->front * velocity;
        if (dir == RIGHT) this->pos += this->right * velocity;
        if (dir == LEFT) this->pos -= this->right * velocity;
        if (dir == UP) this->pos += this->up * velocity;
        if (dir == DOWN) this->pos -= this->up * velocity;

    }

    void LookAround(GLFWwindow* window)
    {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);//hides the  cursor
            if (this->firstClick) //prevents jumping around/ snapping
            {
                glfwSetCursorPos(window, (this->width / 2), (this->height / 2));
                firstClick = false;
            }
            double mouseX, mouseY; //where to store cursor pos
            glfwGetCursorPos(window, &mouseX, &mouseY); //gets cursor pos

            float rotX = this->mouseSens * (float)(mouseY - (this->height / 2)) / this->height;
            float rotY = this->mouseSens * (float)(mouseX - (this->height / 2)) / this->height;

            //prevents a barrel roll
            glm::vec3 newFront = glm::rotate(this->front, glm::radians(-rotX), glm::normalize(glm::cross(this->front, this->up))); 
            if (abs(glm::angle(newFront, this->up) - glm::radians(90.0f)) <= glm::radians(85.0f))
            {
                this->front = newFront;
            }
            //rotates the camera arounnd
            this->front = glm::rotate(this->front, glm::radians(-rotY), this->up);
            glfwSetCursorPos(window, (width / 2), (height / 2));
        }
        else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            firstClick = true;

        }

    }

    void ProcessMouseScroll(GLfloat yOffset)
    {
        float velocity = this->movementSpeed * 0.2;

        if (yOffset > 0) this->pos += this->front * velocity;
        if (yOffset < 0) this->pos -= this->front * velocity;
    }



private:
    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 pos;
    glm::vec3 right;



    bool firstClick = true;
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
   // this->right = glm::vec3(1.0f, 0.0f, 0.0f);
   this->right = glm::normalize(glm::cross(this->front, this->up)); 
    //this->up = glm::normalize(glm::cross(this->right, this->front));
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

