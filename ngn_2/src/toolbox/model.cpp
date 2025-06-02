#include "model.h"
#include <iostream>

Model::Model() {

  this->verts = {
      // Front face (position XYZ + color RGB)
      -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // 0: Red
      0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  // 1: Green
      0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,   // 2: Blue
      -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,  // 3: Yellow

      // Back face
      -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, // 4: Magenta
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  // 5: Cyan
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,   // 6: White
      -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f   // 7: Black
  };
  this->idxs = {// Front face
                0, 1, 2, 2, 3, 0,

                // Right face
                1, 5, 6, 6, 2, 1,

                // Back face
                5, 4, 7, 7, 6, 5,

                // Left face
                4, 0, 3, 3, 7, 4,

                // Top face
                3, 2, 6, 6, 7, 3,

                // Bottom face
                4, 5, 1, 1, 0, 4};

  glCreateVertexArrays(1, &this->m_vao);
  glBindVertexArray(this->m_vao);

  glCreateBuffers(1, &this->m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
  glBufferData(GL_ARRAY_BUFFER, this->verts.size() * sizeof(float),
               this->verts.data(), GL_STATIC_DRAW);

  glCreateBuffers(1, &this->m_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               this->idxs.size() * sizeof(unsigned int), this->idxs.data(),
               GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));

  glBindVertexArray(0);

  this->m_Shader = std::make_unique<Shader>();
}

void Model::renderModel() {
  this->m_Shader->useShader();
  glBindVertexArray(this->m_vao);
  glDrawElements(GL_TRIANGLES, this->idxs.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  std::cout << this->idxs.size() << std::endl;
}

void Model::destroyModel() {
  this->m_Shader->destroyShader();
  this->m_Shader = 0;
  glDeleteBuffers(1, &this->m_vbo);
  this->m_vbo = 0;
  glDeleteBuffers(1, &this->m_ibo);
  this->m_ibo = 0;
  glDeleteVertexArrays(1, &this->m_vao);
  this->m_vao = 0;
}
