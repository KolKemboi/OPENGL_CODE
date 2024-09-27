#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* objVerts = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main() {\n"
"    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

const char* objFrags = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"    FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n"
"}\0";

const char* quad_shader = R"(
#version 330 core;
layout (location = 0) 
)";

float verts[] =
{
	//VERTS 
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
};

unsigned int idx[] =
{
	0, 1, 2,
	2, 3, 0,
};

float quadverts[] =
{
	//VERTS 
	1.0f, 1.0f, 0.0f, 
	1.0f, -1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
};

unsigned int quadidx[] =
{
	0, 1, 2,
	2, 3, 0,
};

unsigned int width = 800, height = 800;
unsigned int vao, vbo, ebo;
unsigned int vert, frag, shadProg;
unsigned int quadvao, quadvbo, quadebo;
unsigned int quadvert, quadfrag, quadshadProg;


void closeWindow(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)glfwSetWindowShouldClose(window, true);
}

void genBuffers(unsigned int& vertexArray, unsigned int& vertexBuffer, unsigned int& elementBuffer, float* vertices, unsigned int* indices, size_t vertSize, size_t idxSize);

void checkShaderCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n";
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n";
		}
	}
}

void genShader(unsigned int& vertexShader, unsigned int& fragmentShader, unsigned int& shaderProgram, const char* vertSource, const char* fragSource)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertSource, NULL);
	glCompileShader(vertexShader);
	checkShaderCompileErrors(vertexShader, "VERTEX");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSource, NULL);
	glCompileShader(fragmentShader);
	checkShaderCompileErrors(fragmentShader, "FRAGMENT");

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkShaderCompileErrors(shaderProgram, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Basics", nullptr, nullptr);
	if (window == NULL)
	{
		std::cerr << "ERROR::FAILED TO CREATE WINDOW" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, static_cast<unsigned int>(width), static_cast<unsigned int>(height));

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	genBuffers(vao, vbo, ebo, verts, idx, sizeof(verts), sizeof(idx));
	genShader(vert, frag, shadProg, objVerts, objFrags);

	genBuffers(quadvao, quadvbo, quadebo, quadverts, quadidx, sizeof(quadverts), sizeof(quadidx));

	while (!glfwWindowShouldClose(window))
	{
		closeWindow(window);

		glClearColor(0.2, 0.1, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shadProg);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, sizeof(idx) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		glBindVertexArray(quadvao);
		//glDrawElements(GL_TRIANGLES, sizeof(quadidx) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

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
	glDeleteBuffers(1, &ebo);
	
	glDeleteVertexArrays(1, &quadvao);
	glDeleteBuffers(1, &quadvbo);
	glDeleteBuffers(1, &quadebo);

	glfwDestroyWindow(window);
	glfwTerminate();
}
void genBuffers(unsigned int& vertexArray, unsigned int& vertexBuffer, unsigned int& elementBuffer, float* vertices, unsigned int* indices, size_t vertSize, size_t idxSize)
{

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxSize, indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



}