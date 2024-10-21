#include "VAO.h"

VAO::VAO(){
	glGenVertexArrays(1, &VertexArrays);
}

void VAO::LinkAttrib(VBO& VertBufferObj, GLuint Layout, GLint NumComponents, GLenum Type, GLsizei Stride, void* Offset){
	VertBufferObj.Bind();
	glVertexAttribPointer(Layout, NumComponents, Type, GL_FALSE, Stride, Offset);
	glEnableVertexAttribArray(Layout);
	VertBufferObj.Unbind();
}

void VAO::Bind() {
	glBindVertexArray(VertexArrays);
}

void VAO::Unbind() {
	glBindVertexArray(0);
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &VertexArrays);
}