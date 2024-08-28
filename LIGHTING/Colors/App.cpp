#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.hpp"

const unsigned int width = 800, height = 800;

GLfloat vertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  // Vertex 0
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  // Vertex 1
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // Vertex 2
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  // Vertex 3

    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,// Vertex 4
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,// Vertex 5
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,// Vertex 6
    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,// Vertex 7
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



int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Colors", nullptr, nullptr);
	if (window == NULL)
	{
		std::cerr << "Failed" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);
	glEnable(GL_DEPTH_TEST);


    GLuint boxVAO, boxVBO, boxEBO;

    glGenVertexArrays(1, &boxVAO);
    glBindVertexArray(boxVAO);

    glGenBuffers(1, &boxVBO);
    glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &boxEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Shader boxShader("default.vert", "default.frag");

	while (!(glfwWindowShouldClose(window)))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        boxShader.UseShader();
        glBindVertexArray(boxVAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
	}

    glDeleteVertexArrays(1, &boxVAO);
    glDeleteBuffers(1, &boxVBO);
    glDeleteBuffers(1, &boxEBO);
	glfwDestroyWindow(window);
	glfwTerminate();
}