#pragma once
#include "VBO.h"

class VAO{
public:
	GLuint VertexArrays;
	VAO();

	void LinkAttrib(VBO& VBO, GLuint Layout, GLuint NumComponents, GLenum Type, GLuint Stride, GLuint* offset);


	void Bind();
	void Unbind();
	void Delete();
};

