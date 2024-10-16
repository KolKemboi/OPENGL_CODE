#include "EBO.h"

EBO::EBO() {
	glGenBuffers(1, &this->ElementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ElementBuffer);

}

void EBO::LinkData(GLuint* indices, GLsizei size){
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

}

void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ElementBuffer);
}

void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() {
	glDeleteBuffers(1, &this->ElementBuffer);
}