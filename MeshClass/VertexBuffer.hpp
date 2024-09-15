#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
};

class VertexBuffer
{
public:
	VertexBuffer(std::vector<Vertex> verts);
	~VertexBuffer();
	void BindVertBuffer();
	void UnbindVertBuffer();
private:
	GLuint vertexBuffer;
};

VertexBuffer::VertexBuffer(std::vector<Vertex> verts)
{
	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &this->vertexBuffer);
}

void VertexBuffer::BindVertBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
}

void VertexBuffer::UnbindVertBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
