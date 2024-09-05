#pragma once

#include <glad/glad.h>

class ElementBuffer
{
public:
	ElementBuffer(GLuint* Indices, GLsizeiptr Size);
	~ElementBuffer();
	void BindElemBuffer();
	void UnbindElemBuffer();
private:
	GLuint elementBuffer;
};

ElementBuffer::ElementBuffer(GLuint* Indices, GLsizeiptr Size)
{
	glGenBuffers(1, &this->elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, Indices, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &this->elementBuffer);
}

void ElementBuffer::BindElemBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);
}

void ElementBuffer::UnbindElemBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
