#include "shader.h"

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
    gl_Position = projection * view * model * vec4(position, 1.0);
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

}

void Shader::destroyShader() {

}

unsigned int Shader::returnShader() const {
  return this->m_Shader;
}

void Shader::useShader() const {
  glUseProgram(this->m_Shader);
}
