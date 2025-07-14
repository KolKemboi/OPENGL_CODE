#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>
#include <vector>
#ifndef _GLAD_HEADER_
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include "Shader.hpp"
#include "Camera.hpp"

class Model{
public:
	Model();
	unsigned int m_Vao;
	void DestroyModel();
	void renderModel();
	void SetModelLoc();

private:
	std::shared_ptr<Camera> m_Camera;
	std::shared_ptr<Shader> m_Shader;
	std::vector<float> m_Vertdata;
	std::vector<unsigned int> m_Idxdata;
	unsigned int m_Vbo, m_Ibo, m_ModelLoc;
	glm::mat4 m_Model;
};
