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
	Shader m_Shader;
	u_int m_IndexCount;

	Mesh() : m_Vao(0), m_Vbo(0), m_Ibo(0), 
		m_Transform(Transform(glm::vec3(0.0), glm::vec3(0.0), glm::vec3(0.0))), m_Shader(), m_IndexCount(0)
	{
		
	};

	Mesh(u_int vao, u_int vbo, u_int ibo, Transform transform, Shader shader, u_int indexCount) : m_Vao(vao), m_Vbo(vbo), m_Ibo(ibo),
		m_Transform(transform), m_Shader(shader), m_IndexCount(indexCount)
	{

	}
};

Mesh createMesh(float* vertices, GLsizei vertexCount, u_int* indices, u_int indexCount,
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f))
{
	u_int vao, vbo, ibo;
	Transform meshTransform(pos, scale, rot);
	Shader shader;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount, indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);

	return Mesh(vao, vbo, ibo, meshTransform, shader, indexCount);
}