#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

#include "Camera.h"
#include "Shader.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
};

class Mesh
{
public:
	unsigned int VAO;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices )
	{
		this->vertices = vertices;
		this->indices = indices;
		this->setUpMesh();
	}
	
	void Draw(Shader& shader, Camera& camera)
	{
		camera.setCamVecs(shader);

		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(this->indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	

private:
	unsigned int VBO, EBO;

	void setUpMesh()
	{
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
		
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

		glBindVertexArray(0);

	}
};