#pragma once
#include <glad/glad.h>

class shaderClass
{
public:
	GLuint ShaderProg, VertShader, FragShader;

	shaderClass();

	void UseShader();
	void DeleteShader();

};

