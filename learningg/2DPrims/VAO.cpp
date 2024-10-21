#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &this->VertexArray);
	glBindVertexArray(this->VertexArray);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLint NumComponents, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.Bind();
	glVertexAttribPointer(layout, NumComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind()
{
	glBindVertexArray(this->VertexArray);
}

// Unbinds the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &this->VertexArray);
}