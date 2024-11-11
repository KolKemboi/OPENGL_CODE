#pragma once

#include <glad/glad.h>
#include <sstream>
#include <fstream>
#include <cerrno>
#include <string>

class Shader
{
public:
	Shader(const char* VertexFile, const char* FragmentFile);
	~Shader();
	std::string get_file_contents(const char* filename);
	void UseShader();
	GLuint ShaderProgram;
private:
	GLuint VertexShader, FragmentShader;
};

Shader::Shader(const char* VertexFile, const char* FragmentFile)
{
	std::string VertexInfo = get_file_contents(VertexFile);
	std::string FragmentInfo = get_file_contents(FragmentFile);

	const char* vertSource = VertexInfo.c_str();
	const char* fragSource = FragmentInfo.c_str();

	this->VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->VertexShader, 1, &vertSource, 0);
	glCompileShader(this->VertexShader);
	
	this->FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->FragmentShader, 1, &fragSource, 0);
	glCompileShader(this->FragmentShader);

	this->ShaderProgram = glCreateProgram();
	glAttachShader(this->ShaderProgram, this->VertexShader);
	glAttachShader(this->ShaderProgram, this->FragmentShader);
	glLinkProgram(this->ShaderProgram);
}

Shader::~Shader()
{
	glDeleteShader(this->VertexShader);
	glDeleteShader(this->FragmentShader);
	glDeleteProgram(this->ShaderProgram);
}

std::string Shader::get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string fileCont;
		in.seekg(0, std::ios::end);
		fileCont.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&fileCont[0], fileCont.size());
		in.close();
		return fileCont;
	}
	throw(errno);
}

void Shader::UseShader()
{
	glUseProgram(this->ShaderProgram);
}
