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

const unsigned int width = 800;
const unsigned int height = 800;

GLfloat verts[] = {
	// Front face
	-0.5f, -0.5f,  0.5f,  // Vertex 0
	 0.5f, -0.5f,  0.5f,  // Vertex 1
	 0.5f,  0.5f,  0.5f,  // Vertex 2
	-0.5f,  0.5f,  0.5f,  // Vertex 3

	// Back face
	-0.5f, -0.5f, -0.5f,  // Vertex 4
	 0.5f, -0.5f, -0.5f,  // Vertex 5
	 0.5f,  0.5f, -0.5f,  // Vertex 6
	-0.5f,  0.5f, -0.5f,  // Vertex 7
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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 0, 0);
	
	VAO1.Unbind();
	EBO1.Unbind();

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.UseShader();
		VAO1.Bind();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));//moving the camera backwards
		proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);//FOV, aspect ratio, min clipping and max clipping

		int modelLoc = glGetUniformLocation(shader.ShaderProg, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shader.ShaderProg, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shader.ShaderProg, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

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