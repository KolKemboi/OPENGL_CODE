#pragma once

#include <glad/glad.h>

class ElementBuffer
{
public:
	ElementBuffer(GLuint* Indices, GLsizeiptr Size);
	~ElementBuffer();
	void Bind();
	void Unbind();
private:
	unsigned int elementBuffer;

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


void ElementBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);
}

void ElementBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
