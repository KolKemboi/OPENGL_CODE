#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO {
public:
	GLuint ElementBuffer;

	EBO(GLuint* indices);

	void Bind();
	void Unbind();
	void Delete();
};


#endif // !EBO_CLASS_H
