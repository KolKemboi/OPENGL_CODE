#pragma once

#ifndef GLAD_GUARD_
#include <glad/glad.h>
#endif

class Shader {
public:
  Shader();
  void useShader() const;
  void destroyShader();
  unsigned int returnShader() const;

private:
  unsigned int m_Shader, v_Shader, f_Shader;
};
