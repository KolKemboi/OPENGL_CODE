#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

const unsigned int width = 800;
const unsigned int height = 800;

GLfloat verts[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
};

GLuint indices[] = {
	0, 1, 2,
	0, 2, 3,
};

class Engine {
public:
	Engine() {
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		this->window = glfwCreateWindow(width, height, "SQUARE_PRIMITIVE", NULL, NULL);
		if (window == NULL) {
			std::cerr << "Error In Window Formation" << std::endl;
			glfwTerminate();
		}
		
		glfwMakeContextCurrent(window);
		gladLoadGL();
		glViewport(0, 0, 800, 800);

		//create the shader, EBO, VBO and EBO

		this->myVAO = std::make_unique<VAO>();
		this->myVBO = std::make_unique<VBO>();
		this->myEBO = std::make_unique<EBO>();

		myVBO->LinkData(verts, sizeof(verts));
		myEBO->LinkData(indices, sizeof(indices));

		this->myshader = std::make_unique<Shader>("default.vert", "default.frag");

		myEBO->Bind();
		myVAO->LinkAttrib(*myVBO, 0, 3, GL_FLOAT, 3 * (sizeof(float)), (void*)0);

		myVAO->Unbind();
		myEBO->Unbind();
	}

	~Engine() {
		glfwDestroyWindow(window);
		myEBO->Delete();
		myVBO->Delete();
		myVAO->Delete();
		myshader->Delete();
		glfwTerminate();
		std::cout << "Destructor Successful" << std::endl;
	}
	void Run() {
		while (!glfwWindowShouldClose(window)) {
			glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			myshader->Activate();
			myVAO->Bind();
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}


private:
	GLFWwindow* window;
	std::unique_ptr<VAO> myVAO;
	std::unique_ptr<VBO> myVBO;
	std::unique_ptr<EBO> myEBO;
	std::unique_ptr<Shader> myshader;
};
