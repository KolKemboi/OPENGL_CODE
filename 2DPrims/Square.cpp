#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

class Engine{
public:
	Engine() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		CreateWindow();
		if (window == NULL) {
			std::cerr << "Error In Window Formation" << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);
		gladLoadGL();
		glViewport(0, 0, 800, 800);
	}

	~Engine() {
		glfwDestroyWindow(window);
		std::cout << "It Has Run" << std::endl;
	}
	void Run(Shader& ShaderProgram, VAO& VertexArray) {
		while (!glfwWindowShouldClose(window)) {
			glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			ShaderProgram.Activate();
			VertexArray.Bind();
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	void CreateWindow() {
		window = glfwCreateWindow(width, height, "SQUARE_PRIMITIVE", NULL, NULL);
	}

private:
	GLFWwindow* window;
};


int main() {
	
	
	Engine Render;
	
	Shader ShaderProgram("default.vert", "default.frag");
	//Creating the VAO, VBO and EBO
	VAO VertexArray;

	VBO VertexBuffer;
	EBO ElementBuffer;
	VertexBuffer.LinkData(verts, sizeof(verts));
	ElementBuffer.LinkData(indices, sizeof(indices));
	
	VertexArray.LinkAttrib(VertexBuffer, 0, 3, GL_FLOAT, 3*(sizeof(float)), (void*)0);

	VertexArray.Unbind();
	VertexBuffer.Unbind();
	ElementBuffer.Unbind();

	Render.Run(ShaderProgram, VertexArray);

	VertexArray.Delete();
	VertexBuffer.Delete();
	ElementBuffer.Delete();
	ShaderProgram.Delete();
	glfwTerminate();
	return 0;
}
