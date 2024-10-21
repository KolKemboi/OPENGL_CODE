#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "InputPolling.h"

void closeWindow(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)glfwSetWindowShouldClose(window, true);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 800, 800);
	Inputs inputsHandler(window);

	inputsHandler.Callback();


	while (!glfwWindowShouldClose(window))
	{
		//closeWindow(window);
		glClearColor(0.2, 0.1, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		std::string crntKey = inputsHandler.keyPressed();

		
		std::cout << crntKey << std::endl;

		if (crntKey == "Escape") glfwSetWindowShouldClose(window, true);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();





	
}