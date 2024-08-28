#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Camera.hpp"

const unsigned int width = 800, height = 800;

GLfloat vertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f,  // Vertex 0
     0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f,  // Vertex 1
     0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f,  // Vertex 2
    -0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f,  // Vertex 3

    // Back face
    -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f,// Vertex 4
     0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f,// Vertex 5
     0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f,// Vertex 6
   - 0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f,// Vertex 7
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

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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

    GLuint lightVAO;

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);


    Shader boxShader("default.vert", "default.frag");
    Shader lightShader("color.vert", "color.frag");
    Camera camera;

	while (!(glfwWindowShouldClose(window)))
	{ 
		glfwPollEvents();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightShader.UseShader();

        glm::mat4 lightmodel = glm::mat4(1.0f);
        lightmodel = glm::translate(lightmodel, lightPos);
        lightmodel = glm::scale(lightmodel, glm::vec3(0.2f));
        GLint lightmodelLoc = glGetUniformLocation(lightShader.ShaderProgram, "model");
        glUniformMatrix4fv(lightmodelLoc, 1, GL_FALSE, glm::value_ptr(lightmodel));



        glBindVertexArray(lightVAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        glBindVertexArray(lightVAO);
         
        boxShader.UseShader();

        GLint objectColorLoc = glGetUniformLocation(boxShader.ShaderProgram, "objColor");
        GLint lightColorLoc = glGetUniformLocation(boxShader.ShaderProgram, "lightColor");

        glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
        glUniform3f(lightColorLoc, 1.0f, 0.5f, 1.0f);

        //model transforms
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        GLint modelLoc = glGetUniformLocation(boxShader.ShaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        //camera funcs
        camera.setCamera(boxShader);
        camera.LookAround(window);


        glBindVertexArray(boxVAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        glBindVertexArray(boxVAO);

		glfwSwapBuffers(window);
	}

    glDeleteVertexArrays(1, &boxVAO);
    glDeleteBuffers(1, &boxVBO);
    glDeleteBuffers(1, &boxEBO);
	glfwDestroyWindow(window);
	glfwTerminate();
}