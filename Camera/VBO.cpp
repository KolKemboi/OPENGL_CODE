#include "VBO.h"

VBO::VBO(GLfloat* data, GLsizeiptr size){
	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);//pass the data instead of the reference to the data
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
}

void VBO::Unbind(){
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	glDeleteBuffers(1, &VertexBuffer);
}