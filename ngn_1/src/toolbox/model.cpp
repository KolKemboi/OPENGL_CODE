#include "model.h"
#include "shader.h"
#include <iostream>
#include <memory>

// TODO: make the VAO, VBO, IBO for all of them, add a basic shader

void Model::makeModel() {

this->verts = {
    // Front face
    -0.5f, -0.5f,  0.5f,  // 0
     0.5f, -0.5f,  0.5f,  // 1
     0.5f,  0.5f,  0.5f,  // 2
    -0.5f,  0.5f,  0.5f,  // 3

    // Back face
    -0.5f, -0.5f, -0.5f,  // 4
     0.5f, -0.5f, -0.5f,  // 5
     0.5f,  0.5f, -0.5f,  // 6
    -0.5f,  0.5f, -0.5f   // 7
};

this->idxs = {
    // Front face
    0, 1, 2,
    2, 3, 0,

    // Right face
    1, 5, 6,
    6, 2, 1,

    // Back face
    5, 4, 7,
    7, 6, 5,

    // Left face
    4, 0, 3,
    3, 7, 4,

    // Top face
    3, 2, 6,
    6, 7, 3,

    // Bottom face
    4, 5, 1,
    1, 0, 4
};

  glCreateVertexArrays(1, &this->m_vao);
  glBindVertexArray(this->m_vao);

  glCreateBuffers(1, &this->m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
  glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(),
               GL_STATIC_DRAW);

  glCreateBuffers(1, &this->m_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxs.size() * sizeof(unsigned int),
               idxs.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  glBindVertexArray(0);

  this->m_Shader = std::make_shared<Shader>();
}

void Model::renderModel() {
  std::cout << this->verts.size() << std::endl;
  std::cout << this->idxs.size() << std::endl;

  this->m_Shader->activateShader();
  glBindVertexArray(this->m_vao);

  glDrawElements(GL_TRIANGLES, this->idxs.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Model::destroyModel() {
  glDeleteVertexArrays(1, &this->m_vao);
  this->m_vao = 0;
  glDeleteBuffers(1, &this->m_ibo);
  this->m_ibo = 0;
  glDeleteBuffers(1, &this->m_vbo);
  this->m_vbo = 0;
}
