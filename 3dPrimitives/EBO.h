#pragma once
#include <glad/glad.h>
class EBO
{
public:
	GLuint ElementBuffer;

	EBO(GLuint* Indices, GLsizeiptr Size);
	void Bind();
	void Unbind();
	void Delete();
};

