#pragma once

#include <glad/glad.h>
#include <vector>

class ElementBuffer
{
public:
	ElementBuffer(std::vector<GLuint>& indices);
	~ElementBuffer();
	void BindElemBuffer();
	void UnbindElemBuffer();
private:
	GLuint elementBuffer;
};

ElementBuffer::ElementBuffer(std::vector<GLuint>& indices)
{
	glGenBuffers(1, &this->elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
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
