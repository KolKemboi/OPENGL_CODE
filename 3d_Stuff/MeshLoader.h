/*
	Every mesh has a VAO, VBO, IBO,
	It also has a shader
	And A transform
*/
#pragma once 
#include <glm/glm.hpp>
#include "Shader.h"
typedef unsigned int u_int;

struct Transform
{
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_Rotation;

	Transform(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation)
		: m_Position(pos), m_Scale(scale), m_Rotation(rotation)
	{

	}

};

struct Mesh
{
	u_int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	Shader m_Shader;
	Transform m_Transform;
	u_int m_indexCount;
	
	Mesh()
		: m_VertexArray(0), m_VertexBuffer(0), m_IndexBuffer(0), m_Shader(), m_Transform(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f)), m_indexCount(0)
	{
	}

	Mesh(u_int vao, u_int vbo, u_int ibo, Shader shader, u_int indexCount, Transform transform)
		: m_VertexArray(vao), m_VertexBuffer(vbo), m_IndexBuffer(ibo),m_Shader(shader), m_Transform(transform), m_indexCount(indexCount)
	{

	}

};

Mesh mesh_creator(float *vertices, GLsizei vertexCount, u_int *indices, u_int indexCount,
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f))
{
	u_int vao = 0, vbo = 0, ibo = 0;

	Shader meshShader;

	Transform transform(pos, scale, rot);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount, vertices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u_int) * indexCount, indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);


	return Mesh(vao, vbo, ibo, meshShader, indexCount, transform);
}