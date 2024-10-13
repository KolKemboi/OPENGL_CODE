#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Entity.hpp"
#include <memory>
#include <iostream>

typedef unsigned int u_int;
template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
Ref<T> Reffed (Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

class Engine
{
public:
	Engine()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		this->m_Window = glfwCreateWindow(this->m_Width, this->m_Height, "ECS", nullptr, nullptr);
		glfwMakeContextCurrent(this->m_Window);

		gladLoadGL();
		glViewport(0, 0, static_cast<u_int>(this->m_Width), static_cast<u_int>(this->m_Height));
		glEnable(GL_DEPTH_TEST);

		createModelEntity(registry, "untitled.obj");


	}
	~Engine()
	{
		glfwDestroyWindow(this->m_Window);
		glfwTerminate();
	}
	void RunEngine()
	{
		while (!(glfwWindowShouldClose(this->m_Window)))
		{
			this->closeWindow(this->m_Window);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
			renderSystem(registry);

			glfwSwapBuffers(this->m_Window);
			glfwPollEvents();
		}
	}

private:
	GLFWwindow* m_Window;
	u_int m_Width = 1280, m_Height = 1028;
	entt::registry registry;

	void closeWindow(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(m_Window, true);
	}

};






