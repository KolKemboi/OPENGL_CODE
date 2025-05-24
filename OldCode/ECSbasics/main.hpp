#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Entity.hpp"
#include <memory>
#include <iostream>

typedef unsigned int u_int;

// Smart pointer utility for shared resources
template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
Ref<T> Reffed(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

class Engine
{
public:
    Engine()
    {
        // Initialize GLFW and set window hints for OpenGL context
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create window and context
        this->m_Window = glfwCreateWindow(this->m_Width, this->m_Height, "ECS", nullptr, nullptr);
        if (!this->m_Window)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(this->m_Window);

        // Load OpenGL functions using GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            glfwDestroyWindow(this->m_Window);
            glfwTerminate();
            return;
        }

        // Set OpenGL viewport and enable depth testing
        glViewport(0, 0, static_cast<u_int>(this->m_Width), static_cast<u_int>(this->m_Height));
        glEnable(GL_DEPTH_TEST);

        // Load and create the model entity (ensure the model path is correct)
        CreateModelEntity(registry, "untitled.obj");
    }

    ~Engine()
    {
        // Clean up the window and terminate GLFW
        glfwDestroyWindow(this->m_Window);
        glfwTerminate();
    }

    void RunEngine()
    {
        // Main rendering loop
        while (!glfwWindowShouldClose(this->m_Window))
        {
            // Check for window close conditions (e.g., ESC key press)
            this->closeWindow(this->m_Window);

            // Clear buffers (color and depth)
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.2f, 0.1f, 0.3f, 1.0f);

            // Render the scene (implement RenderSystem to handle entity rendering)
            RenderSystem(registry, glm::mat4(1.0f), glm::mat4(1.0f));

            // Swap buffers and poll for events
            glfwSwapBuffers(this->m_Window);
            glfwPollEvents();
        }
    }

private:
    GLFWwindow* m_Window;
    u_int m_Width = 1280, m_Height = 720; // Corrected height
    entt::registry registry;

    // Close window on ESC key press
    void closeWindow(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(m_Window, true);
        }
    }
};
