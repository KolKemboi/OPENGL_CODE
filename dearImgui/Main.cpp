#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const unsigned int width = 800;
const unsigned int height = 800;

GLfloat Verts[] = {
	0.5f, 0.5f, 0.0f,
   -0.5f, 0.5f, 0.0f,
   -0.5f,-0.5f, 0.0f,
};

GLuint Indices[] = {
	0, 1, 2,
};

const char* VertSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"uniform float size;\n"
"void main(){\n"
"	gl_Position = vec4(size * aPos.x, size * aPos.y, size * aPos.z, 1.0f);\n"
"}\n\0";

const char* FragSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 color;\n"
"void main(){\n"
"	FragColor = color;\n"
"}\n\0";

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "ImGui", NULL, NULL);
	if (window == NULL) {
		std::cout << "failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	GLuint ShaderProg, VertShader, FragShader;

	VertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertShader, 1, &VertSource, NULL);
	glCompileShader(VertShader);

	FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragShader, 1, &FragSource, NULL);
	glCompileShader(FragShader);

	ShaderProg = glCreateProgram();
	glAttachShader(ShaderProg, VertShader);
	glAttachShader(ShaderProg, FragShader);
	glLinkProgram(ShaderProg);

	glDeleteShader(VertShader);
	glDeleteShader(FragShader);

	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	bool drawTriangle = true;
	float size = 1.0f;
	float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };
	glUseProgram(ShaderProg);
	glUniform1f(glGetUniformLocation(ShaderProg, "size"), size);
	glUniform4f(glGetUniformLocation(ShaderProg, "color"), color[0], color[1], color[2], color[3]);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		glUseProgram(ShaderProg);
		glBindVertexArray(VAO);
		if (drawTriangle){
			glDrawElements(GL_TRIANGLES, sizeof(Indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		}
		ImGui::Begin("ImGui Window");
		ImGui::Text("Hello World");
		ImGui::Checkbox("Draw", &drawTriangle);
		ImGui::SliderFloat("size", &size, 0.5f, 2.0f);
		ImGui::ColorEdit4("color", color);
		ImGui::End();

		glUseProgram(ShaderProg);
		glUniform1f(glGetUniformLocation(ShaderProg, "size"), size);
		glUniform4f(glGetUniformLocation(ShaderProg, "color"), color[0], color[1], color[2], color[3]);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glDeleteProgram(ShaderProg);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();
}