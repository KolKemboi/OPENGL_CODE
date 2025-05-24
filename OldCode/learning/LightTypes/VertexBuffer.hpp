#pragma once

#include <glad/glad.h>

class VertexBuffer
{
public:
	VertexBuffer(GLfloat* Vertices, GLsizeiptr Size);
	~VertexBuffer();
	void BindVertBuffer();
	void UnbindVertBuffer();
private:
	GLuint vertexBuffer;
};

VertexBuffer::VertexBuffer(GLfloat* Vertices, GLsizeiptr Size)
{
	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, Size, Vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &this->vertexBuffer);
}

void VertexBuffer::BindVertBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
}

void VertexBuffer::UnbindVertBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
