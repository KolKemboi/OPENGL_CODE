#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader(const char* vertfile, const char* fragfile);
	~Shader();
	std::string get_file_cont(const char* filename);
	void useShader();
	unsigned int ShaderProgram;
private:
	unsigned int VertShader, FragShader;

};

Shader::Shader(const char* vertfile, const char* fragfile)
{
	std::string verttext = get_file_cont(vertfile);
	std::string fragtext = get_file_cont(fragfile);
	
	const char* VertSource = verttext.c_str();
	const char* FragSource = fragtext.c_str();

	this->VertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->VertShader, 1, &VertSource, nullptr);
	glCompileShader(this->VertShader);

	this->FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->FragShader, 1, &FragSource, nullptr);
	glCompileShader(this->FragShader);

	this->ShaderProgram = glCreateProgram();
	glAttachShader(this->ShaderProgram, this->VertShader);
	glAttachShader(this->ShaderProgram, this->FragShader);
	glLinkProgram(this->ShaderProgram);

	glDeleteShader(this->VertShader);
	glDeleteShader(this->FragShader);

}

Shader::~Shader()
{
	glDeleteProgram(this->ShaderProgram);
}

std::string Shader::get_file_cont(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string cont;
		in.seekg(0, std::ios::end);
		cont.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&cont[0], cont.size());
		in.close();
		return cont;
	}
	else
	{
		std::cerr << "Failed to read cont" << std::endl;
	}
}

void Shader::useShader()
{
	glUseProgram(this->ShaderProgram);
}

