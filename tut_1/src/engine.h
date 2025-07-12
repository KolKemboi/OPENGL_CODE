#pragma once
#include <GLFW/glfw3.h>
#include "configs.h"

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

    vk::Instance instance { nullptr };

    void make_instance();

    vk::DebugUtilsMessengerEXT debugMessenger{ nullptr };

    vk::DispatchLoaderDynamic dldi;

    void make_debug_messenger();
};


