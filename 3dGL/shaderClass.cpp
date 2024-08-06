#include "shaderClass.h"
#include <cstddef>


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 color;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 proj;\n"
"uniform mat4 camMatrix;\n"
"void main()\n"
"{\n"
"    gl_Position = camMatrix * vec4(aPos, 1.0f);\n"
"    color = aColor;\n"
"}\n\0";


const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 color;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(color, 1.0f);\n"
"}\n\0";



shaderClass::shaderClass()
{
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertShader);

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragShader);

	ShaderProg = glCreateProgram();
	glAttachShader(ShaderProg, vertShader);
	glAttachShader(ShaderProg, fragShader);
	glLinkProgram(ShaderProg);

}

void shaderClass::UseShader()
{
	glUseProgram(ShaderProg);
}

void shaderClass::DeleteShader()
{
	glDeleteProgram(ShaderProg);
}
