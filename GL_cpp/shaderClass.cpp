#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}


Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();
	
	
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertexSource, NULL);
	glCompileShader(vertShader);
	compileErrors(vertShader, "VERTEX");

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragmentSource, NULL);
	glCompileShader(fragShader);
	compileErrors(fragShader, "FRAGMENT");


	shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vertShader);
	glAttachShader(shaderProg, fragShader);
	glLinkProgram(shaderProg);
	compileErrors(shaderProg, "SHADER");


	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

}

void Shader::Activate()
{
	glUseProgram(shaderProg);
}
void Shader::Delete()
{
	glDeleteProgram(shaderProg);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}