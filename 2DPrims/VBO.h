#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO {
	public:
		GLuint VertexBuffer;

		VBO();
		void LinkData(GLfloat* verts, GLsizei size);
		void Bind();
		void Unbind();
		void Delete();
};

#endif // !VBO_CLASS_H
