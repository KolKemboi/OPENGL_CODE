#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Entity.hpp"

typedef unsigned int u_int;

u_int width = 800, height = 800;

void closeWindow(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "ECS", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 800, 800);

	glEnable(GL_DEPTH_TEST);

	entt::registry registry;
	CreateEntity(registry, "pointlight.obj");
	CreateEntity(registry, "sun.obj");

	while (!(glfwWindowShouldClose(window)))
	{
		closeWindow(window);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glClearColor(0.2, 0.1, 0.3, 1.0);

		Render(registry, glm::mat4(1.0f), glm::mat4(1.0f));

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}
