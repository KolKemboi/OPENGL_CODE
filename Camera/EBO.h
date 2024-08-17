#pragma once
#include <glad/glad.h>

class EBO
{
public:
	GLuint ElementBuffer;

	EBO(GLuint* data, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

