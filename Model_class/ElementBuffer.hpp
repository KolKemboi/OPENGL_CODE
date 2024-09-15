#pragma once

#include <glad/glad.h>

class ElementBuffer
{
public:
	ElementBuffer(std::vector <unsigned int>& idxs);
	~ElementBuffer();
	void BindElemBuffer();
	void UnbindElemBuffer();
private:
	GLuint elementBuffer;
};

ElementBuffer::ElementBuffer(std::vector <unsigned int>& idxs)
{
	glGenBuffers(1, &this->elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxs.size()*sizeof(unsigned int), idxs.data(), GL_STATIC_DRAW);
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
