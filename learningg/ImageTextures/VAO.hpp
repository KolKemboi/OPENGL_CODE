#pragma once

#include <glad/glad.h>
#include "VBO.hpp"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void Unbind();
	void LinkAttrib(VertexBuffer& vertBuffObj, GLuint Layout, GLint NumComponents, GLenum Type, GLsizei Stride, void* Offset);
private:
	unsigned int vertexArray;
};

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &this->vertexArray);
	glBindVertexArray(this->vertexArray);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &this->vertexArray);
}

void VertexArray::Bind()
{
	glBindVertexArray(this->vertexArray);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::LinkAttrib(VertexBuffer& vertBuffObj, GLuint Layout, GLint NumComponents, GLenum Type, GLsizei Stride, void* Offset)
{
	vertBuffObj.Bind();
	glVertexAttribPointer(Layout, NumComponents, Type, GL_FALSE, Stride, (void*)Offset);
	glEnableVertexAttribArray(Layout);
	vertBuffObj.Unbind();
}

