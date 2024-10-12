#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


typedef unsigned int u_int;


u_int width = 1280, height = 1024;
glm::vec3 pos = glm::vec3(0.0f, 0.5f, 3.5f);
glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 model, view, projection;

const char* vertexShaderSrc = R"(
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	color = aCol;
}
)";

const char* fragmentShaderSrc = R"(
#version 330 core

out vec4 FragColor;

in vec3 color;

void main()
{
	FragColor = vec4(color, 1.0);
}
)";

float vertices[] =
{
	 0.5,  0.5, -0.5, 1.0, 0.0, 0.0,
	 0.5, -0.5,  0.5, 0.0, 1.0, 0.0,
	-0.5, -0.5,  0.5, 0.0, 0.0, 1.0,
	-0.5,  0.5, -0.5, 1.0, 1.0, 1.0,

};
u_int indices[] = 
{
	0, 1, 2,
	2, 3, 0,
};

void closeWindow(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "SOME WINDOW", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "OPENGL_ERROR::FAILED_TO_CREATE_WINDOW" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
	glEnable(GL_DEPTH_TEST);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	u_int vao, vbo, ibo, vertex, fragment, shaderProg;

	//--------------------------BUFFER STUFF-------------------------------
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//-----------------------------SHADER STUFF--------------------------------
	vertex = glCreateShader(GL_VERTEX_SHADER);	
	glShaderSource(vertex, 1, &vertexShaderSrc, 0);
	glCompileShader(vertex);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);	
	glShaderSource(fragment, 1, &fragmentShaderSrc, 0);
	glCompileShader(fragment);

	shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vertex);
	glAttachShader(shaderProg, fragment);
	glLinkProgram(shaderProg);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	while (!(glfwWindowShouldClose(window)))
	{
		closeWindow(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2, 0.1, 0.3, 1.0);

		glUseProgram(shaderProg);
		//------get uniform data then set the model, view and projection matrices----------------

		model = glm::mat4(1.0f);
		glUniformMatrix4fv(glGetUniformLocation(shaderProg, "model"), 1, GL_FALSE, glm::value_ptr(model));

		view = glm::lookAt(pos, pos + front, up);
		glUniformMatrix4fv(glGetUniformLocation(shaderProg, "view"), 1, GL_FALSE, glm::value_ptr(view));

		projection = glm::perspective(45.0f, (float)(width / height), 0.1f, 1000.0f);
		glUniformMatrix4fv(glGetUniformLocation(shaderProg, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(u_int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Scene");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);

	glDeleteProgram(shaderProg);
	glfwDestroyWindow(window);
	glfwTerminate();

}



