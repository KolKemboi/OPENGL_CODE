#pragma once

#include <glad/glad.h>
#include "VertexBuffer.hpp"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void BindVertArray();
	void UnbindVertArray();
	void LinkAttribArray(VertexBuffer& VertBuffObj, GLuint Layout, GLint NumComponents, GLenum Type, GLsizei Stride, void* Offset);
private:
	GLuint vertexArray;
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

void VertexArray::BindVertArray()
{
	glBindVertexArray(this->vertexArray);
}

void VertexArray::UnbindVertArray()
{
	glBindVertexArray(0);
}

void VertexArray::LinkAttribArray(VertexBuffer& VertBuffObj, GLuint Layout, GLint NumComponents, GLenum Type, GLsizei Stride, void* Offset)
{
	VertBuffObj.BindVertBuffer();
	glVertexAttribPointer(Layout, NumComponents, Type, GL_FALSE, Stride, (void*)Offset);
	glEnableVertexAttribArray(Layout);
	VertBuffObj.UnbindVertBuffer();
}
