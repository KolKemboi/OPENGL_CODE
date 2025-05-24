#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Window {


public:
    Window(unsigned int width, unsigned int height, const std::string& title)
        : m_Width(width), m_Height(height), m_Title(title) {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            throw std::runtime_error("GLFW Initialization Failed");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
        if (!m_Window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            throw std::runtime_error("GLFW Window Creation Failed");
        }

        glfwMakeContextCurrent(m_Window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            throw std::runtime_error("GLAD Initialization Failed");
        }

        glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow*, int width, int height) {
            glViewport(0, 0, width, height);
            });
    }

    ~Window() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    GLFWwindow* GetGLFWWindow() const { return m_Window; }
    bool ShouldClose() const { return glfwWindowShouldClose(m_Window); }
private:
    GLFWwindow* m_Window;
    unsigned int m_Width, m_Height;
    std::string m_Title;
};
