#pragma once

#include <glad/glad.h>

class ElementBuffer
{
public:
	ElementBuffer();
	~ElementBuffer();
	void LinkData(GLuint* indices, GLsizeiptr size);
	void BindElementBuffer();
	void UnbindElementBuffer();
private:
	GLuint elementBuffer;
};

ElementBuffer::ElementBuffer()
{
	glGenBuffers(1, &this->elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &this->elementBuffer);
}

void ElementBuffer::LinkData(GLuint* indices, GLsizeiptr size)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void ElementBuffer::BindElementBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);
}

void ElementBuffer::UnbindElementBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
