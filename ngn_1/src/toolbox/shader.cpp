#include "shader.h"
#include "model.h"
#include <iostream>

const char *vertShaderSrc = R"(
  #version 330 core
  layout (location = 0) in vec3 position;
  void main()
  {
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
  }
)";
const char *fragShaderSrc = R"(
  #version 330 core
  out vec4 color;
  void main()
  {
    color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
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
  glAttachShader(this->m_Shader, this->f_Shader);
  glAttachShader(this->m_Shader, this->v_Shader);
  glLinkProgram(this->m_Shader);
  glGetProgramiv(this->m_Shader, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(this->m_Shader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER_LINKING" << infoLog << std::endl;
  }

  glad_glDeleteShader(this->f_Shader);
  
}

void Shader::deleteShader() { glad_glDeleteProgram(this->m_Shader); }

void Shader::activateShader() { glUseProgram(this->m_Shader); }
