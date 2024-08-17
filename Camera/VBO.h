#pragma once
#include <glad/glad.h>

class VBO
{
public:
	GLuint VertexBuffer;

	VBO(GLfloat* data, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

