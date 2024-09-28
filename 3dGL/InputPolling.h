#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Inputs
{
public:
    Inputs(GLFWwindow* window)
    {
        this->window = window;
        instance = this;
        std::fill(std::begin(keys), std::end(keys), false); 
    }

    void destroyClass()
    {
        if (instance == this)
            instance = nullptr;
    }

    void Callback()
    {
        glfwSetKeyCallback(window, keyCallback);
    }

    void checkKey()
    {
        if (instance && instance->keys[GLFW_KEY_W]) std::cout << "W key is pressed" << std::endl;
        if (instance && instance->keys[GLFW_KEY_A]) std::cout << "A key is pressed" << std::endl;
        if (instance && instance->keys[GLFW_KEY_S]) std::cout << "S key is pressed" << std::endl;
        if (instance && instance->keys[GLFW_KEY_D]) std::cout << "D key is pressed" << std::endl;
    }

private:
    bool keys[1024]; 
    GLFWwindow* window;

    static Inputs* instance;

    static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode)
    {
        if (instance) 
        {
            if (key >= 0 && key < 1024) 
            {
                if (action == GLFW_PRESS)
                    instance->keys[key] = true;
                else if (action == GLFW_RELEASE)
                    instance->keys[key] = false;
            }
        }
    }
};

Inputs* Inputs::instance = nullptr;
