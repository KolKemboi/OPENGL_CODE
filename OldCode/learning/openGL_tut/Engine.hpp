#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"


GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,//Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,//Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,//Upper Corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,//Inner Left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,//Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,//Inner Down
};

GLuint indices[] =
{
	0, 3, 5, //lower left Triangle
	3, 2, 4, //lower right Triangle
	5, 4, 1, //upper triangle
};
class Engine
{
public:
	Engine();
	~Engine();
	void CreateWindow();
	void RunEngine();
private:
	GLFWwindow* window;
	std::unique_ptr<VAO> myVAO;
	std::unique_ptr<VBO> myVBO;
	std::unique_ptr<EBO> myEBO;
	std::unique_ptr<Shader> myShader;
};

Engine::Engine()
{
	glfwInit();


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	CreateWindow();
	if (window == NULL)
	{
		std::cerr << "Terminated" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glClearColor(0.17f, 0.13f, 0.17f, 1.0f);
	glViewport(0, 0, 800, 800);

	this->myVAO = std::make_unique<VAO>();
	this->myVBO = std::make_unique<VBO>(vertices, sizeof(vertices));
	this->myEBO = std::make_unique<EBO>(indices, sizeof(indices));

	myEBO->Bind();
	myVAO->LinkAttrib(*myVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	myVAO->Unbind();
	myEBO->Unbind();

	this->myShader = std::make_unique<Shader>();
}

Engine::~Engine()
{
	myEBO->Delete();
	myShader->Delete();
	myVAO->Delete();
	myVBO->Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Engine::CreateWindow()
{
	this->window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
}

void Engine::RunEngine()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		myShader->Activate();
		myVAO->Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
	}
}
