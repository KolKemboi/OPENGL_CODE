#include "shader.h"
#include <iostream>

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
    gl_Position = model * projection * view * vec4(position, 1.0);
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

  int success;
  char infoLog[512];

  this->v_Shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(this->v_Shader, 1, &vertShaderSrc, NULL);
  glCompileShader(this->v_Shader);
  glGetShaderiv(this->v_Shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(this->v_Shader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::VERTEX_COMPILATION" << infoLog << std::endl;
  }

  this->f_Shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(this->f_Shader, 1, &fragShaderSrc, NULL);
  glCompileShader(this->f_Shader);
  glGetShaderiv(this->f_Shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(this->f_Shader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::FRAGMENT_COMPILATION" << infoLog << std::endl;
  }

  this->m_Shader = glCreateProgram();
  glAttachShader(this->m_Shader, this->v_Shader);
  glAttachShader(this->m_Shader, this->f_Shader);
  glLinkProgram(this->m_Shader);
  glGetProgramiv(this->m_Shader, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(this->m_Shader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER_LINKING_ERROR::" << infoLog << std::endl;
  }
}

void Shader::destroyShader() {
  glDeleteShader(this->f_Shader);
  this->f_Shader = 0;
  glDeleteShader(this->v_Shader);
  this->v_Shader = 0;
  glDeleteProgram(this->m_Shader);
  this->m_Shader = 0;
}

unsigned int Shader::returnShader() const { return this->m_Shader; }

void Shader::useShader() const { glUseProgram(this->m_Shader); }
