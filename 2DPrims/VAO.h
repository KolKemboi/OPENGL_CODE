#ifndef VAO_CLASS_H
#define VAO_CLASS_H
#include <glad/glad.h>
#include "VBO.h"

class VAO {
	public:
		GLuint VertexArray;

		VAO();

		void LinkAttrib(VBO& VBO, GLuint layout, GLuint NumComponents, GLenum type, GLsizeiptr stride, void* offset);

		void Bind();
		void Unbind();
		void Delete();
};

#endif // !VAO_CLASS_H
