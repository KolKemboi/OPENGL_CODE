#pragma once 


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "MeshLoader.h"


typedef unsigned int u_int;

class RenderSystem
{
public:
	void initScene()
	{
		glClearColor(0.2, 0.1, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Render(Mesh& mesh)
	{
		mesh.m_Shader.useShader();
		glBindVertexArray(mesh.m_VertexArray);
		glDrawElements(GL_TRIANGLES, mesh.m_indexCount, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
	void clearScene(GLFWwindow* window)
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

private:

};
