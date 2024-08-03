#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &VertexArrays);
}

void VAO::LinkAttrib(VBO& VBO, GLuint Layout, GLuint NumComponents, GLenum Type, GLuint Stride, GLuint*offset)
{
	VBO.Bind();
	glVertexAttribPointer(Layout, NumComponents, Type, GL_FALSE, Stride, offset);
	glEnableVertexAttribArray(0);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(VertexArrays);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &VertexArrays);
}
