#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO {
public:
	GLuint ElementBuffer;

	EBO();

	void LinkData(GLuint* indices, GLsizei size);
	void Bind();
	void Unbind();
	void Delete();
};


#endif // !EBO_CLASS_H
