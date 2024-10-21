#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <iostream>
#include <string>
#include <cerrno>
#include <glad/glad.h>
#include <sstream>
#include <fstream>

std::string get_file_contents(const char* filename);

class Shader {
public:
	GLuint ShaderProg;

	Shader(const char* vertFile, const char* fragFile);

	void Activate();
	void Delete();
private:
	void compileErrors(unsigned int shader, const char* type);
};


#endif // !SHADER_CLASS_H
