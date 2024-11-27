#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"


typedef unsigned int u_int;



struct Transform
{
	glm::vec3 m_Position, m_Scale, m_Rotation;

	Transform(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot) : m_Position(pos), m_Scale(scale), m_Rotation(rot)
	{
	}

};

struct BaseMesh
{
	u_int m_Vao, m_Vbo, m_Ibo;


	BaseMesh() : m_Vao(0), m_Vbo(0), m_Ibo(0)
	{
		
	}

	void createMesh(/*Requires vertices, indices and their respective sizes*/)
	{
		//create everything for the class
		glGenVertexArrays(1, &m_Vao);
		glBindVertexArray(m_Vao);

	}

};

struct Model : public BaseMesh
{
	ModelShader m_Shader;
};
struct Light : public BaseMesh
{
	LightShader m_Shader;
};





