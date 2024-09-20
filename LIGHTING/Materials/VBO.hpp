#pragma once

#include <glad/glad.h>

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();
	void LinkData(GLfloat* vertices, GLsizeiptr size);
	void BindVertexBuffer();
	void UnbindVertexBuffer();
private:
	GLuint vertexBuffer;
};

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &this->vertexBuffer);
}

void VertexBuffer::LinkData(GLfloat* vertices, GLsizeiptr size)
{
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VertexBuffer::BindVertexBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
}

void VertexBuffer::UnbindVertexBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
