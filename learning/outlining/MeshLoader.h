#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"


typedef unsigned int u_int;



struct Transform
{
	glm::vec3 m_Position, m_Scale, m_Rotation;

	Transform(glm::vec3 pos = glm::vec3(0.0), glm::vec3 scale = glm::vec3(1.0), glm::vec3 rot = glm::vec3(0.0)) 
		: m_Position(pos), m_Scale(scale), m_Rotation(rot)
	{
	}

};

struct Mesh
{
	u_int m_Vao, m_Vbo, m_Ibo;
	Transform m_Transform;
	ModelShader m_ModelShader;
	LightShader m_LightShader;

	Mesh() : m_Vao(0), m_Vbo(0), m_Ibo(0), 
		m_Transform(Transform(glm::vec3(0.0), glm::vec3(0.0), glm::vec3(0.0))), m_ModelShader(), m_LightShader()
	{
		
	};

	Mesh(u_int vao, u_int vbo, u_int ibo, Transform transform) : m_Vao(vao), m_Vbo(vbo), m_Ibo(ibo),
		m_Transform(transform)
	{

	}
};

Mesh createMesh()
{

}