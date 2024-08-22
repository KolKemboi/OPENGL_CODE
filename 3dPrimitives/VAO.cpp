#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &this->VertexArray);
	glBindVertexArray(this->VertexArray);

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
	glBindVertexArray(this->VertexArray);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &this->VertexArray);
}
