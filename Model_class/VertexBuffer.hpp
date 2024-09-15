#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
};

class VertexBuffer
{
public:
	VertexBuffer(std::vector <Vertex>& vertices);
	~VertexBuffer();
	void BindVertBuffer();
	void UnbindVertBuffer();
private:
	GLuint vertexBuffer;
};

VertexBuffer::VertexBuffer(std::vector <Vertex>& vertices)
{
	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
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
