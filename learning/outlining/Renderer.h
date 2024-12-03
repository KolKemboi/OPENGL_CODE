#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MeshLoader.h"

class Renderer
{
public:
	void InitScene()
	{
		glClearColor(0.2, 0.1, 0.3, 1.0);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}

	void Render(Mesh mesh)
	{
		mesh.m_Shader.useShader();
		ApplyTransforms(mesh);

		//FANYA the RENDERING
	}
	void ClearScene(GLFWwindow* window)
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
private:
	void ApplyTransforms(Mesh mesh)
	{

	}
};