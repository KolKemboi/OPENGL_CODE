#pragma once
#include <glad/glad.h>
class VBO
{
public:
	GLuint VertexBuffer;

	VBO(GLfloat *Verts, GLsizeiptr Size);
	void Bind();
	void Unbind();
	void Delete();
};

