#pragma once

#ifndef GLAD_GUARD_
#include "glad/glad.h"
#endif // !GLAD_GUARD_
#include <GLFW/glfw3.h>
#include <iostream>
class Shader {
public:
  unsigned int m_Shader;
  Shader();
  void deleteShader();
  void activateShader();

private:
  unsigned int v_Shader, f_Shader;
};
