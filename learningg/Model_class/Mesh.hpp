#pragma once

#include <string>

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Mesh
{
public:
    Mesh(std::vector <Vertex>& vertices, std::vector <unsigned int>& indices);
    void Draw(Shader& shader, Camera& camera);
private:
    std::vector <Vertex> verts;
    std::vector <unsigned int> idx;
    VertexArray VAO;
};

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <unsigned int>& indices)
{
    this->verts = vertices;
    this->idx = indices;

    VAO.BindVertArray();

    VertexBuffer VBO(this->verts);
    ElementBuffer EBO(this->idx);

    VAO.LinkAttribArray(VBO, 0, 3, GL_FLOAT, 9 * sizeof(Vertex), (void*)0);
    VAO.LinkAttribArray(VBO, 1, 3, GL_FLOAT, 9 * sizeof(Vertex), (void*)(3 * sizeof(float)));
    VAO.LinkAttribArray(VBO, 2, 3, GL_FLOAT, 9 * sizeof(Vertex), (void*)(6 * sizeof(float)));

    VAO.UnbindVertArray();
    VBO.UnbindVertBuffer();
    EBO.UnbindElemBuffer();

}

void Mesh::Draw(Shader& shader, Camera& camera)
{
    shader.UseShader();
    VAO.BindVertArray();

    camera.setCamVectors(shader);
    glDrawElements(GL_TRIANGLES, this->idx.size(), GL_UNSIGNED_INT, 0);

}
