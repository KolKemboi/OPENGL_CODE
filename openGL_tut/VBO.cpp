#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
}

void VBO::Delete() {
	glDeleteBuffers(1, &VertexBuffer);
}