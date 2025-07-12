#include "engine.h"


Engine::Engine()
{
    if(debugMode)
    {
        std::cout << "Vulkan" << std::endl;
    }
    build_glfw_window();
}

void Engine::build_glfw_window()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    if(window = glfwCreateWindow(width, height, "Vulkan Tuts1", nullptr, nullptr))
    {
        if(debugMode)
        {
            std::cout << "Succesfully made a window" << std::endl;
        }
    }
    else
    {
        if(debugMode)
        {
            std::cout << "Failed" << std::endl;
        }
    }
}


Engine::~Engine()
{
    glfwTerminate();
    std::cout << "Deleted" << std::endl;
}