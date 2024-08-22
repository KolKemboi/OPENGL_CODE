#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "shaderClass.h"

const unsigned int width = 800;
const unsigned int height = 800;

// Define the vertices and indices
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

void GL_HINTS() {
    //hinting the glfw I am using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}
int main() {
	glfwInit();
    GL_HINTS();

	GLFWwindow* window = glfwCreateWindow(width, height, "3dPrims", NULL, NULL);
	if (window == NULL) {
		std::cout << "FAILED" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//makes the window the current context in the state
	gladLoadGL();//loads gl
	glViewport(0, 0, 800, 800);//screen space to render in
    //creating the shader program
    shaderClass shader;

    //Creating the VBO, EBO and VAO
    VAO VAO1;
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));
    EBO1.Bind();
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    
    VAO1.Unbind();
    EBO1.Unbind();
    glLineWidth(5.0f);
    glPointSize(10.0f);
    glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.1f, 0.3f, 1.0f);//fills the window with purple
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clears both depth and color buffers

        VAO1.Bind();
        shader.useShaderProgram();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        glDrawElements(GL_POINTS, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);//swaps the buffers
		glfwPollEvents();//processes all pooled events
	}

    VBO1.Delete();
    EBO1.Delete();
    VAO1.Delete();
    shader.deleteShaderProgram();
	glfwTerminate();
}