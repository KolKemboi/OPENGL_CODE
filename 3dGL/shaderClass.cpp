#include "shaderClass.h"
#include <cstddef>


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 proj;\n"
"{\n"
"    gl_Position = proj * view * model * vec4(aPos, 1.0);\n"
"}\n\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
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
