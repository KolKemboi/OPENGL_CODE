#pragma once
#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	GLuint VertexArray;
	VAO();

	void LinkAttrib(VBO& VBO, GLuint Layout, GLint NumComponents, GLenum Type, GLsizei Stride, void*Offset);

	void Bind();
	void Unbind();
	void Delete();
};

