#pragma once

#include <glad/glad.h>
typedef unsigned int u_int;

const char* _vertexShader = 
R"(
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	gl_Position = vec4(aPos, 1.0);
	Normal = aNorm;
}
)";


const char* _fragmentShader = 
R"(

out vec4 FragColor;

in vec3 Normal;

void main()
{
	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}
)";

class Shader
{
public:
	Shader()
	{
		this->m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(this->m_VertexShader, 1, &_vertexShader, 0);
		glCompileShader(this->m_VertexShader);
		
		this->m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(this->m_FragmentShader, 1, &_fragmentShader, 0);
		glCompileShader(this->m_FragmentShader);

		this->m_ShaderProgram = glCreateProgram();
		glAttachShader(this->m_ShaderProgram, this->m_VertexShader);
		glAttachShader(this->m_ShaderProgram, this->m_FragmentShader);
		glLinkProgram(this->m_ShaderProgram);

		glDeleteShader(this->m_FragmentShader);
		glDeleteShader(this->m_VertexShader);

	}
	void ShaderDestroyer()
	{
		glDeleteProgram(m_ShaderProgram);
	}

	void UseShader() const
	{
		glUseProgram(m_ShaderProgram);
	}
	unsigned int RetShaderProgram() const
	{
		return m_ShaderProgram;
	}


private:
	u_int m_VertexShader, m_FragmentShader, m_ShaderProgram;
};