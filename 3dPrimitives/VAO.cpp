#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &VertexArray);
	glBindVertexArray(VertexArray);

}

void VAO::LinkAttrib(VBO& VBO1, GLuint Layout, GLint NumComponents, GLenum Type, GLsizei Stride, void* Offset)
{
	VBO1.Bind();
	glVertexAttribPointer(Layout, NumComponents, Type, GL_FALSE, Stride, Offset);
	glEnableVertexAttribArray(Layout);
	VBO1.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(VertexArray);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &VertexArray);
}
