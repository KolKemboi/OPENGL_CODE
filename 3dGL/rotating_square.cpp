#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "shaderClass.h"
#include "Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

GLfloat verts[] = {
	// Front face
	//verts							//colors
	-0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 1.0f, // Vertex 0
	 0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 0.0f, // Vertex 1
	 0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f, // Vertex 2
	-0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f, // Vertex 3
								
	// Back face				
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,// Vertex 4
	 0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,// Vertex 5
	 0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,// Vertex 6
	-0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 1.0f,// Vertex 7
};

GLuint indices[] = {
	// Front face
	0, 1, 2,
	2, 3, 0,

	// Back face
	4, 5, 6,
	6, 7, 4,

	// Left face
	0, 3, 7,
	7, 4, 0,

	// Right face
	1, 5, 6,
	6, 2, 1,

	// Top face
	3, 2, 6,
	6, 7, 3,

	// Bottom face
	0, 1, 5,
	5, 4, 0,
};


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "3dGL", NULL, NULL);

	if (window == NULL) {
		std::cout << "Error in Window Formation" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(0, 0, 800, 800);

	shaderClass shader;
	
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(verts, sizeof(verts));
	EBO EBO1(indices, sizeof(indices));

	EBO1.Bind();
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3* (sizeof(float))));

	
	VAO1.Unbind();
	EBO1.Unbind();
	//float rot_x = 0.0f;
	//float rot_y = 0.0f;
	//float rot_z = 0.0f;
	//double prevTime = glfwGetTime();
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.UseShader();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shader.DeleteShader();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
