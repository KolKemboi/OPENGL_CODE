#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

enum Camera_Movement
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
    Camera()
    {
        m_Position = glm::vec3(0.0f, 1.0f, 3.5f);
        m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
        m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
        m_Yaw = -90.0f;
        m_Pitch = 0.0f;
        updateCamVectors();
        this->view = glm::mat4(1.0f);
        this->proj = glm::mat4(1.0f);
    }

    void pan(float xOffset, float yOffset, float deltaTime) {
        float speed = m_Speed * deltaTime; // Adjust speed by deltaTime
        m_Position -= m_Right * xOffset * speed;  // Left/right (x-axis pan)
        m_Position += m_Up * yOffset * speed;     // Up/down (y-axis pan)
    }

    void orbit(float xOffset, float yOffset, float deltaTime)
    {
        float sens = m_Sens * deltaTime;
        m_Yaw += xOffset * sens;
        m_Pitch += yOffset * sens;

        if (m_Pitch > 89.0f) m_Pitch = 89.0f;
        if (m_Pitch < -89.0f) m_Pitch = -89.0f; // Fix: Correctly clamping the pitch

        updateCamVectors();
    }
    
    void moveAround(Camera_Movement dir, float deltaTime)
    {
        float velocity = m_WASDSpeed * deltaTime;
        if (dir == FORWARD) m_Position += m_Front * velocity;
        if (dir == BACKWARD) m_Position -= m_Front * velocity;
        if (dir == RIGHT) m_Position += m_Right * velocity;
        if (dir == LEFT) m_Position -= m_Right * velocity;
        if (dir == UP) m_Position += m_Up * velocity;
        if (dir == DOWN) m_Position -= m_Up * velocity;

    }

    void moveForward(float yOffset, float deltaTime)
    {
        float speed = m_Speed * deltaTime; // Adjust speed by deltaTime
        m_Position += m_Front * yOffset * speed;
    }

    void translate(float xOffset, float yOffset, float deltaTime)
    {
        float velocity = m_Speed * deltaTime; // Adjust speed by deltaTime
        m_Position -= m_Right * xOffset * velocity;
        m_Position += m_Up * yOffset * velocity;
    }

    float getZoom() const { return m_CamFOV; }

    glm::mat4 getViewMat() const
    {
        return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }
    float getSpeed() const { return m_WASDSpeed; }

    void setCamVectors(Shader& shader)
    {
        this->view = glm::lookAt(this->m_Position, this->m_Position + this->m_Front, this->m_Up);
        this->proj = glm::perspective(glm::radians(m_CamFOV), (GLfloat)1.0, 0.1f, 1000.0f);

        this->viewLoc = glGetUniformLocation(shader.ShaderProgram, "view");
        this->projLoc = glGetUniformLocation(shader.ShaderProgram, "proj");

        glUniformMatrix4fv(this->viewLoc, 1, GL_FALSE, glm::value_ptr(this->view));
        glUniformMatrix4fv(this->projLoc, 1, GL_FALSE, glm::value_ptr(this->proj));
    }

private:
    glm::mat4 view;
    glm::mat4 proj;

    GLint viewLoc;
    GLint projLoc;
    
    float m_WASDSpeed = 10.0f;
    float m_Speed = 150.0f;
    float m_Sens = 20.0f;
    float m_CamFOV = 45.0f;

    glm::vec3 m_Position, m_Front, m_Up, m_Right;
    float m_Yaw, m_Pitch;

    void updateCamVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

        m_Front = glm::normalize(front);
        m_Right = glm::normalize(glm::cross(m_Front, m_Up));
    }
};
