#pragma once
#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	GLuint VertexArrays;
	VAO();

	void LinkAttrib(VBO& VertBufferObj, GLuint Layout, GLint NumComponents, GLenum Type, GLsizei Stride, void* Offset);
	void Bind();
	void Unbind();
	void Delete();
};

