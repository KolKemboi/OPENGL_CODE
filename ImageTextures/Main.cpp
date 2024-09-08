#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Textures.hpp"


GLfloat lightVertices[] = {
	// Front face
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  // Vertex 0
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  // Vertex 1
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  // Vertex 2
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  // Vertex 3

	// Back face
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Vertex 4
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Vertex 5
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Vertex 6
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Vertex 7
};

GLuint lightIndices[] = {
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


GLfloat objVerts[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
	-1.0f, 0.0f,  1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		1.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

GLuint objIndices[] = {
	0, 1, 2,
	0, 2, 3
};

const unsigned int width = 800, height = 800;
Camera camera(width, height);
int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Image Textures", nullptr, nullptr);

	if (window == NULL)
	{
		std::cerr << "Failed" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);
	glEnable(GL_DEPTH_TEST);

	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//ImGui::StyleColorsDark();
	//ImGui_ImplGlfw_InitForOpenGL(window, true);
	//ImGui_ImplOpenGL3_Init("version 330");

	

	//OBJ DATA
	VertexArray objVAO;
	VertexBuffer objVBO(objVerts, sizeof(objVerts));
	ElementBuffer objEBO(objIndices, sizeof(objIndices));

	objEBO.Bind();

	objVAO.LinkAttrib(objVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	objVAO.LinkAttrib(objVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	objVAO.LinkAttrib(objVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	objVAO.LinkAttrib(objVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float))); 
	
	objVAO.Unbind();
	objEBO.Unbind();
	
	Shader objShader("obj.vert", "obj.frag");

	Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(objShader, "tex0", 0);

	//LIGHT DATA
	VertexArray lightVAO;
	VertexBuffer lightVBO(lightVertices, sizeof(lightVertices));
	ElementBuffer lightEBO(lightIndices, sizeof(lightIndices));

	lightEBO.Bind();
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	lightVAO.LinkAttrib(lightVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	lightVAO.Unbind();
	lightEBO.Unbind();

	Shader lightShader("light.vert", "light.frag");


	
	
	while (!(glfwWindowShouldClose(window)))
	{
		glfwPollEvents();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLfloat currentFrame = glfwGetTime();
		

		//ImGui_ImplGlfw_NewFrame();
		//ImGui_ImplOpenGL3_NewFrame();
		//ImGui::NewFrame();

		////Obj
		objShader.useShader();
		camera.setCamera(objShader);
		int objModelLoc = glGetUniformLocation(objShader.ShaderProgram, "model");
		glm::mat4 objModel = glm::mat4(1.0f);
		objModel = glm::translate(objModel, glm::vec3(-0.5f, 0.0f, 1.0f));
		objModel = glm::rotate(objModel, 10.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(objModelLoc, 1, GL_FALSE, glm::value_ptr(objModel));
		popCat.Bind();

		objVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(objIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		objVAO.Unbind();

		//Light
		lightShader.useShader();
		camera.setCamera(lightShader);
		int lightModelLoc = glGetUniformLocation(lightShader.ShaderProgram, "model");
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::scale(lightModel, glm::vec3(0.5f));
		lightModel = glm::translate(lightModel, glm::vec3(2.0f, 2.0f, -1.0f));
		lightModel = glm::rotate(lightModel, 10.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
		
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		lightVAO.Unbind();

		//ImGui::Render();
		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}


	//ImGui_ImplGlfw_Shutdown();
	//ImGui_ImplOpenGL3_Shutdown();
	//ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
}