#include "Shader.hpp"

const char *vertShaderSrc = R"(
  #version 330 core
  layout (location = 0) in vec3 position;
  layout (location = 1) in vec3 color;

  out vec3 vertexColor;  // pass color to fragment shader

  uniform mat4 model;
  uniform mat4 view;
  uniform mat4 projection;

  void main()
  {
    gl_Position = vec4(position, 1.0);
    vertexColor = color;
  }
)";
const char *fragShaderSrc = R"(
  #version 330 core
  in vec3 vertexColor;  // receive color from vertex shader
  out vec4 color;

  void main()
  {
    color = vec4(vertexColor, 1.0);  // output interpolated color
  }
)";

Shader::Shader() {
  // make the shader, check for compition and linking errors
  this->m_VertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(this->m_VertShader, 1, &vertShaderSrc, NULL);
  glCompileShader(this->m_VertShader);

  this->m_FragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(this->m_FragShader, 1, &fragShaderSrc, NULL);
  glCompileShader(this->m_FragShader);

  this->m_ShaderProg = glCreateProgram();
  glAttachShader(this->m_ShaderProg, this->m_VertShader);
  glAttachShader(this->m_ShaderProg, this->m_FragShader);
  glLinkProgram(this->m_ShaderProg);
}

unsigned int Shader::retShader() const { return this->m_ShaderProg; }

void Shader::useShaderProg() const { glUseProgram(this->m_ShaderProg); }

void Shader::destroyShader() {
	glDeleteShader(this->m_FragShader);
	glDeleteShader(this->m_VertShader);
  glDeleteProgram(this->m_ShaderProg);
  this->m_ShaderProg = 0;
  this->m_VertShader = 0;
  this->m_FragShader = 0;
}
