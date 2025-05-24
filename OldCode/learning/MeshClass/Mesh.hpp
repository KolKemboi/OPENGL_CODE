#pragma once

#include <string>
#include <vector>

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"
#include "Camera.hpp"

class Mesh
{
public:
    Mesh(std::vector<Vertex>& verts, std::vector<unsigned int> idxs);
    void Draw(Shader& shader, Camera& camera);

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    VertexArray VAO;
};

Mesh::Mesh(std::vector<Vertex>& verts, std::vector<GLuint> idxs)
    : vertices(verts), indices(idxs)
{
    VAO.BindVertArray();
    VertexBuffer VBO(vertices);
    ElementBuffer EBO(indices);

    // Assuming a stride of sizeof(Vertex) and vertex attributes are in the correct order
    size_t stride = sizeof(Vertex);
    VAO.LinkAttribArray(VBO, 0, 3, GL_FLOAT, stride, (void*)offsetof(Vertex, position));
    VAO.LinkAttribArray(VBO, 1, 3, GL_FLOAT, stride, (void*)offsetof(Vertex, normal));
    VAO.LinkAttribArray(VBO, 2, 3, GL_FLOAT, stride, (void*)offsetof(Vertex, color));

    VAO.UnbindVertArray();
    VBO.UnbindVertBuffer();
    EBO.UnbindElemBuffer();
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
    shader.UseShader();
    VAO.BindVertArray();

	camera.setCamVectors(shader);

	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
}
