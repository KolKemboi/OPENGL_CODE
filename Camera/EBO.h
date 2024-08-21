#pragma once
#include <glad/glad.h>

class EBO
{
public:
	GLuint ElementBuffer;

	EBO(GLuint* data, GLsizeiptr size);//Pass the pointer to the data

	void Bind();
	void Unbind();
	void Delete();
};

