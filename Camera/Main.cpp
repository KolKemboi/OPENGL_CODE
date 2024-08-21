#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

void WindowHints() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
GLFWwindow* CreateWindow(const unsigned int width, const unsigned int height) {
	GLFWwindow* window = glfwCreateWindow(width, height, "Camera Funcs", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		std::cout << "Failed" << std::endl;
	}
	return window;
}

GLfloat vertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  // Vertex 0
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  // Vertex 1
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  // Vertex 2
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  // Vertex 3

    // Back face
    -0.5f, -0.5f, -0.5f,  0.5f, 0.1f, 0.5f,// Vertex 4
     0.5f, -0.5f, -0.5f,  0.5f, 0.1f, 0.5f,// Vertex 5
     0.5f,  0.5f, -0.5f,  0.5f, 0.1f, 0.5f,// Vertex 6
    -0.5f,  0.5f, -0.5f,  0.5f, 0.1f, 0.5f,// Vertex 7
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

const unsigned int width = 800;
const unsigned int height = 800;

int main() {
	glfwInit();
	WindowHints();
	GLFWwindow* window = CreateWindow(width, height);
	glfwMakeContextCurrent(window);
	gladLoadGL(); 
	glViewport(0, 0, 800, 800);

    //GLuint VAO, VBO, EBO;
    //glGenVertexArrays(1, &VAO);
    //glBindVertexArray(VAO);

    //glGenBuffers(1, &VBO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glGenBuffers(1, &EBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*(sizeof(float)), (void*)0);
    //glEnableVertexAttribArray(0);
    //
    //glBindVertexArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));
    EBO1.Bind();
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6*(sizeof(float)), (void*)0);
    
    VAO1.Unbind();
    EBO1.Unbind();


	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /*glBindVertexArray(VAO);*/
          VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
	}

    VBO1.Delete();
    EBO1.Delete();
    VAO1.Delete();
    
    glfwDestroyWindow(window);
	glfwTerminate();
}
