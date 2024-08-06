#include "shaderClass.h"
#include <cstddef>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   color = aColor;\n"
"}\n\0";

const char* fragmentShaderSource= "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 color;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(color, 1.0f);\n"
"}\n\0";


shaderClass::shaderClass() {
	VertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertShader, 1, &vertexShaderSource, NULL);
	glCompileShader(VertShader);
	
	FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(FragShader);

	ShaderProg = glCreateProgram();
	glAttachShader(ShaderProg, VertShader);
	glAttachShader(ShaderProg, FragShader);
	glLinkProgram(ShaderProg);

	glDeleteShader(VertShader);
	glDeleteShader(FragShader);

}

void shaderClass::useShaderProgram() {
	glUseProgram(ShaderProg);
}

void shaderClass::deleteShaderProgram() {
	glDeleteProgram(ShaderProg);
}