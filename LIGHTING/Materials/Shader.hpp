#pragma once

#include <glad/glad.h>
#include <fstream>
#include <cerrno>
#include <sstream>
#include <iostream>
#include <string>

class Shader
{
public:
	GLuint ShaderProgram, VertexShader, FragmentShader;
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();
	void UseShader();

private:
	std::string get_file_cont(const char* filename);


};

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertSourceStr = get_file_cont(vertexFile);
	std::string fragSourceStr = get_file_cont(fragmentFile);

	const char* vertSource = vertSourceStr.c_str();
	const char* fragSource = fragSourceStr.c_str();

	this->VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->VertexShader, 1, &vertSource, nullptr);
	glCompileShader(this->VertexShader);

	this->FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->FragmentShader, 1, &fragSource, nullptr);
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

void Shader::UseShader()
{
	glUseProgram(this->ShaderProgram);
}

std::string Shader::get_file_cont(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string fileContent;
		in.seekg(0, std::ios::end);
		fileContent.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&fileContent[0], fileContent.size());
		in.close();
		return fileContent;
	}
	else
	{
		std::cerr << "count find files" << std::endl;
		throw (errno);
	}
}