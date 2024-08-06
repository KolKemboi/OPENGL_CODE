#include "EBO.h"

EBO::EBO(GLuint* Indices, GLsizeiptr Size){
	glGenBuffers(1, &ElementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, Indices, GL_STATIC_DRAW);
}

void EBO::Bind(){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBuffer);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ElementBuffer);
}
