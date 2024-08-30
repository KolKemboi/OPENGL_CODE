#pragma once
#include <glad/glad.h>
#include "VBO.hpp"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void BindVertexArray();
	void UnbindVertexArray();
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

void VertexArray::BindVertexArray()
{
	glBindVertexArray(this->vertexArray);
}

void VertexArray::UnbindVertexArray()
{
	glBindVertexArray(0);
}

void VertexArray::LinkAttribArray(VertexBuffer& VertBuffObj, GLuint Layout, GLint NumComponents, GLenum Type, GLsizei Stride, void* Offset)
{
	VertBuffObj.BindVertexBuffer();
	glVertexAttribPointer(Layout, NumComponents, Type, GL_FALSE, Stride, Offset);
	glEnableVertexAttribArray(Layout);
	VertBuffObj.UnbindVertexBuffer();
}
