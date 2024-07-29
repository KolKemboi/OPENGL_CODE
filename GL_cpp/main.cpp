#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"

const unsigned int width = 800;
const unsigned int height = 800;

GLfloat verts[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     1.0f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "error" << std::endl;
		glfwTerminate();
		return 0;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(verts, sizeof(verts));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.shaderProg, "scale");

	Texture metalTexture("image_texture.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	metalTexture.texUnit(shaderProgram, "tex0", 0);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.1f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60) {
			rotation += 0.05f;
			prevTime = crntTime;
		}

		glm::mat4 model = glm::mat4(1.0f); //model matrix
		glm::mat4 view = glm::mat4(1.0f); //view matrix
		glm::mat4 proj = glm::mat4(1.0f); //projection matrix

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f)); //rotating the 3d model about the y axis-vertical axis
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f)); //moving the world back
		proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f); //creating the perspective and min and max clipping

		int modelLoc = glGetUniformLocation(shaderProgram.shaderProg, "model"); //getting the model uniform
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(shaderProgram.shaderProg, "view"); //getting the view uniform
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		
		int projLoc = glGetUniformLocation(shaderProgram.shaderProg, "proj"); //getting the projection uniform
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
		
		glUniform1f(uniID, 1.5f);
		metalTexture.Bind();
		VAO1.Bind();
		
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	metalTexture.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}