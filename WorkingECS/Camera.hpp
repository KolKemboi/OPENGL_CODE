#pragma once
#include <glm/glm.hpp>
#include "Shader.hpp"

class Camera {
public:
    Camera() : m_Pos(0.0f, 3.5f, 2.0f), m_Front(0.0f, 0.0f, -1.0f), m_Up(0.0f, 1.0f, 0.0f),
        m_FOV(45.0f), m_NearPlane(0.1f), m_FarPlane(1000.0f), m_View(1.0f), m_Projection(1.0f) {}

    void SetMatrices(Shader& shader) {
        // Logic to set view and projection matrices
    }

private:
    glm::vec3 m_Pos, m_Front, m_Up;
    float m_FOV, m_NearPlane, m_FarPlane;
    glm::mat4 m_View, m_Projection;
};
