#include "VBO.h"

VBO::VBO(GLfloat* Verts, GLsizeiptr Size){
	glGenBuffers(1, &this->VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, Size, Verts, GL_STATIC_DRAW);
}

void VBO::Bind(){
	glBindBuffer(GL_ARRAY_BUFFER, this->VertexBuffer);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &this->VertexBuffer);
}
