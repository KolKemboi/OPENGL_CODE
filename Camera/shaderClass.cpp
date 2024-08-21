#include "shaderClass.h"
#include <cstddef>

const char* vertSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 color;\n"
"void main(){\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"	color = aColor;\n"
"}\n\0";

const char* fragSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 color;\n"
"void main(){\n"
"	FragColor = vec4(color, 1.0);\n"
"}\n\0";

shaderClass::shaderClass()
{
	VertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertShader, 1, &vertSource, NULL);
	glCompileShader(VertShader);

	FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragShader, 1, &fragSource, NULL);
	glCompileShader(FragShader);

	ShaderProg = glCreateProgram();
	glAttachShader(ShaderProg, VertShader);
	glAttachShader(ShaderProg, FragShader);
	glLinkProgram(ShaderProg);

	glDeleteShader(VertShader);
	glDeleteShader(FragShader);
}



void shaderClass::UseShader()
{
	glUseProgram(ShaderProg);
}

void shaderClass::DeleteShader()
{
	glDeleteProgram(ShaderProg);
}
