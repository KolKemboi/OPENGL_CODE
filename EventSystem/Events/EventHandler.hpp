#pragma once

#include "Events.hpp"
#include "MouseEvents.hpp"
#include "WindowEvents.hpp"
#include "../Camera.hpp"
#include "GLFW/glfw3.h"

class EventHandler
{
public:
    EventHandler(Camera& camera)
        : m_Camera(camera), m_FirstMouse(true), m_LastX(0.0), m_LastY(0.0), m_DeltaTime(0.0f) {}

    void setDeltaTime(float deltaTime)
    {
        m_DeltaTime = deltaTime;
    }

    void onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.dispatch<MouseMovement>([this](MouseMovement& e)
            {
                OnMouseMove(e);
            });

        dispatcher.dispatch<MouseScrollEvent>([this](MouseScrollEvent& e)
            {
                onMouseScroll(e);
            });

        dispatcher.dispatch<WindowResizeEvent>([this](WindowResizeEvent& e)
            {
                onWindowResize(e);
            });

        // Process keyboard input for WASD controls
        processKeyboardInput();
    }

private:
    Camera& m_Camera;
    bool m_FirstMouse;
    double m_LastX, m_LastY;
    float m_DeltaTime;

    void OnMouseMove(MouseMovement& event)
    {
        double xPos = event.getX();
        double yPos = event.getY();

        if (m_FirstMouse)
        {
            m_LastX = xPos;
            m_LastY = yPos;
            m_FirstMouse = false;
        }

        float xOffset = xPos - m_LastX;
        float yOffset = yPos - m_LastY;

        // Only process input if the middle mouse button is pressed
        if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
            // Check if Shift is pressed (pan)
            if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
                glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
                m_Camera.pan(xOffset, yOffset, m_DeltaTime); // Pan (x and y axes)
            }
            // Check if Control is pressed (move forward/backward)
            else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
                glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
                m_Camera.moveForward(-yOffset, m_DeltaTime); // Move forward/backward
            }
            // No modifier keys, default to orbiting
            else {
                m_Camera.orbit(-xOffset, yOffset, m_DeltaTime); // Orbit around a target
            }
        }

        // Update last mouse positions for the next frame
        m_LastX = xPos;
        m_LastY = yPos;
    }

    void onMouseScroll(MouseScrollEvent& event)
    {
        // Scroll up/down moves camera forward/backward
        m_Camera.moveForward(event.getYOffset(), m_DeltaTime);
    }

    void onWindowResize(WindowResizeEvent& event)
    {
        glViewport(0, 0, event.getWidth(), event.getHeight());
    }

    void processKeyboardInput()
    {
        // Adjust camera movement speed
        float cameraSpeed = m_Camera.getSpeed();

        // WASD camera movement
        if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
            m_Camera.moveAround(FORWARD, m_DeltaTime);
        }
        if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
            m_Camera.moveAround(BACKWARD, m_DeltaTime);
            // Move backward
        }
        if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
            m_Camera.moveAround(LEFT, m_DeltaTime);
            // Move left
        }
        if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
            m_Camera.moveAround(RIGHT, m_DeltaTime);
            // Move right
        }
    }
};
