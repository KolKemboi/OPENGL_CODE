#pragma once
#include <memory>
#include <vector>
#ifndef _GLAD_HEADER_
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include "Shader.hpp"

class Model{
public:
	Model();
	unsigned int m_Vao;
	void DestroyModel();
	void renderModel();
private:
	std::shared_ptr<Shader> m_Shader;
	std::vector<float> m_Vertdata;
	std::vector<unsigned int> m_Idxdata;
	unsigned int m_Vbo, m_Ibo;
};
