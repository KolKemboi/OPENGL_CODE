#pragma once
#include <glad/glad.h>
class shaderClass
{
public:
	GLuint ShaderProg, vertShader, fragShader;
	
	shaderClass();
	void UseShader();
	void DeleteShader();


};

