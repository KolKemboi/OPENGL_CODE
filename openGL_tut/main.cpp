#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
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
	
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,//Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,//Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,//Upper Corner
		-0.5f/2, 0.5f * float(sqrt(3)) / 6, 0.0f,//Inner Left
		0.5f/2, 0.5f * float(sqrt(3)) / 6, 0.0f,//Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,//Inner Down
	};

	GLuint indices[] = {
		0, 3, 5, //lower left Triangle
		3, 2, 4, //lower right Triangle
		5, 4, 1, //upper triangle
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Terminated" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glClearColor(0.17f, 0.13f, 0.17f, 1.0f);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);//compile the vertex shader

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);//bind the VBO
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);//bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glViewport(0, 0, 800, 800);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.17f, 0.13f, 0.17f, 1.0f);//specify the color of the bs
		glClear(GL_COLOR_BUFFER_BIT);//clean the back buffer
		glUseProgram(shaderProgram);//tell OpenGL whet shader program we want to use
		glBindVertexArray(VAO);//bind the  VAO so opengl knows to use it
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);//swap the buffers



		glfwPollEvents();//take care of all events
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
};