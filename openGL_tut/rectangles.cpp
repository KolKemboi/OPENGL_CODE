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
	glfwInit();//initing glfw

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//hinting which major version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//hinting which minor version
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//hinting the profile
	
	GLfloat verts[] = {
		0.5f, 0.5f, 0.0f, //top left
		0.5f, -0.5f, 0.0f, //bottom left
		-0.5f, -0.5f, 0.0f, //bottom right
		-0.5f, 0.5f, 0.0f, //top right
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3,
	};


	GLFWwindow* window = glfwCreateWindow(800, 800, "Rectangles", NULL, NULL);//creating the window

	//some error checking
	if (window == NULL) {
		std::cout << "Window Failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);//making the window the context
	gladLoadGL();//loading glad

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);//creating the vert shader
	glShaderSource(vertShader, 1, &vertexShaderSource, NULL);//grabbing the vert shader source
	glCompileShader(vertShader);//precompiling the vert shader

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);//creating the frag shader
	glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);//grabbing the frag shader source
	glCompileShader(fragShader);//precompiling the frag shader

	GLuint shaderProgram = glCreateProgram();//creating a shader program
	glAttachShader(shaderProgram, vertShader);//attaching the vert shader
	glAttachShader(shaderProgram, fragShader);//attaching the frag shader
	glLinkProgram(shaderProgram);//linking the shader program

	//deleting both the vert and frag shader because they are already compiled
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	GLuint VAO, VBO, EBO;//creating the VAO and the VBO

	glGenVertexArrays(1, &VAO);//generating the VAO
	glGenBuffers(1, &VBO);//generating the VBO)
	glGenBuffers(1, &EBO);//generating the EBO)
	//binding the VAO first then the VAO
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//introducing the verts to the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//introducing the verts to the VBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glViewport(0, 0, 800, 800);
	//keeping the window alive
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.01f, 0.2f, 0.1f, 1.0f);//changing the bg color
		glClear(GL_COLOR_BUFFER_BIT);//clearing the color buffer bit
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);//swapping the back buffer and front buffer


		glfwPollEvents();//processing all polled events in memory
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);//destroying the already made window
	glfwTerminate();//terminating glfw
	return 0;
}