#pragma once

#include <glad/glad.h>

class VertexBuffer
{
public:
	VertexBuffer(GLfloat* Vertices, GLsizeiptr Size);
	~VertexBuffer();
	void Bind();
	void Unbind();
private:
	unsigned int vertexBuffer;

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


void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
