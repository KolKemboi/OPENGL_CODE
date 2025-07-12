#include "engine.h"
#include "instance.h"

Engine::Engine()
{
    if(debugMode)
    {
        std::cout << "Vulkan" << std::endl;
    }
    build_glfw_window();

    make_instance();
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

void Engine::make_instance()
{
    instance = vkInit::make_instance(debugMode, "ID Tech 12");
}

Engine::~Engine()
{
    glfwTerminate();
    instance.destroy();
    std::cout << "Deleted" << std::endl;
}