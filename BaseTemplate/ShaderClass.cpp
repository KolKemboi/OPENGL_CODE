#include "ShaderClass.h"

std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary); 
		if (in) {
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return (contents);
		}
		throw(errno);
	
}

Shader::Shader(const char* vertFile, const char* fragFile) {
	std::string vertCode = get_file_contents(vertFile);
	std::string fragCode = get_file_contents(fragFile);

	const char* vertSource = vertCode.c_str();
	const char* fragSource = fragCode.c_str();

	GLuint VertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertShader, 1, &vertSource, NULL);
	glCompileShader(VertShader);
	compileErrors(VertShader, "VERTEX");

	GLuint FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragShader, 1, &fragSource, NULL);
	glCompileShader(FragShader);
	compileErrors(FragShader, "FRAGMENT");

	ShaderProg = glCreateProgram();
	glAttachShader(ShaderProg, VertShader);
	glAttachShader(ShaderProg, FragShader);
	glLinkProgram(ShaderProg);

	glDeleteShader(VertShader);
	glDeleteShader(FragShader);
}

void Shader::Activate() {
	glUseProgram(ShaderProg);
}

void Shader::Delete() {
	glDeleteProgram(ShaderProg);
}

void Shader::compileErrors(unsigned int shader, const char* type) {
	GLint hasCompiled;
	char infoLog[1024];

	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << infoLog << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << infoLog << std::endl;
		}
	}
}

