#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Events.hpp"


typedef unsigned int u_int;


u_int width = 800, height = 800;

void closeWindow(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Events", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, static_cast<u_int>(width), static_cast<u_int>(height));


	EventDispatcher dispatcher;
	EventHandler eventHandler(dispatcher, camera);


	Mouse::SetEventDispatcher(&dispatcher);
	Keyboard::SetEventDispatcher(&dispatcher);
	Window::SetEventDispatcher(&dispatcher);

	glfwSetCursorPosCallback(window, Mouse::MousePositionCallback);
	glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
	glfwSetKeyCallback(window, Keyboard::keyCallback);
	glfwSetFramebufferSizeCallback(window, Window::FrameBufferSizeCallback);
	glfwSetScrollCallback(window, Mouse::MouseScrollCallback);



	while (!(glfwWindowShouldClose(window)))
	{
		eventHandler.UpdateDeltaTime();

		//closeWindow(window);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1, 0.1, 0.1, 1.0);

		if (eventHandler.IsLeftMousePressed())
		{
			auto pos = eventHandler.GetMousePos();
			std::cout << "Left mouse button pressed at: (" << pos["mouseX"] << ", " << pos["mouseY"] << ")" << std::endl;
		}

		if (eventHandler.IsRightMousePressed())
		{
			auto pos = eventHandler.GetMousePos();
			std::cout << "Right mouse button pressed at: (" << pos["mouseX"] << ", " << pos["mouseY"] << ")" << std::endl;
		}

		if (eventHandler.IsMiddleMousePressed())
		{
			auto pos = eventHandler.GetMousePos();
			std::cout << "Middle mouse button pressed at: (" << pos["mouseX"] << ", " << pos["mouseY"] << ")" << std::endl;
		}

		if(Keyboard::IsKeyPressed(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, true);

		if (Keyboard::IsKeyPressed(GLFW_KEY_LEFT_CONTROL ))
			std::cout << "controlcontrolcontrolcontrolcontrolcontrolcontrol" << std::endl;
		
		std::unordered_map<std::string, int> windowSize = eventHandler.GetWindowSize();
		//std::cout << "Window Size: " << windowSize["width"] << " x " << windowSize["height"] << std::endl;

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();


}