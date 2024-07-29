#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const unsigned int width = 800;
const unsigned int height = 800;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos, 1.0);\n"
"}\n\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";




int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "SQUARE_PRIMITIVE", NULL, NULL);
	if (window == NULL) {
		std::cout << "Error In Window Formation" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	//Creating the shader Program
	GLuint VertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertShader, 1, &vertexShaderSource, NULL);
	glCompileShader(VertShader);

	GLuint FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(FragShader);

	GLuint ShaderProg = glCreateProgram();
	glAttachShader(ShaderProg, VertShader);
	glAttachShader(ShaderProg, FragShader);
	glLinkProgram(ShaderProg);

	//Creating the VAO, VBO and EBO



	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(ShaderProg);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}