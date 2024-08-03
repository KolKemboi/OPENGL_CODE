#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &vertBuffer);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(0);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(vertBuffer);

}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &vertBuffer);
}
