#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>

class Engine
{    
public:
    Engine();
    ~Engine();
    
private:
    bool debugMode = true;
    void build_glfw_window();

    int width { 640 };
    int height { 480 };
    GLFWwindow* window { nullptr };

};


