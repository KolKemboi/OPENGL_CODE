#pragma once

#ifndef _GLAD_GUARD_
#include <glad/glad.h>
#endif
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
  Shader();
  unsigned int retShader() const;
  void destroyShader();
	void useShaderProg() const;

private:
  unsigned int m_ShaderProg, m_VertShader, m_FragShader;
};
