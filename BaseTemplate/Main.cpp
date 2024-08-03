#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

const unsigned int width = 800;
const unsigned int height = 800;

GLfloat verts[] = {
	0.5f, 0.5f, 0.0f,
   -0.5f,-0.5f, 0.0f,
   -0.5f, 0.5f, 0.0f,
};
GLuint indices[] = {
	0, 1, 2,
};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "BaseTemplate", NULL, NULL);
	if (!window) {
		glfwTerminate();
		std::cout << "Failed" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);
	
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(verts, sizeof(verts));
	EBO EBO1(indices, sizeof(indices));
	EBO1.Bind();
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 0, 0);
	VAO1.Unbind();
	EBO1.Unbind();

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VBO1.Delete();
	VAO1.Delete();
	EBO1.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}