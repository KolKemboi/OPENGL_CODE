#include "VBO.h"

VBO::VBO() {
	glGenBuffers(1, &this->VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->VertexBuffer);

}

void VBO::LinkData(GLfloat* verts, GLsizei size)
{
	glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);

}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, this->VertexBuffer);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	glDeleteBuffers(1, &this->VertexBuffer);
}