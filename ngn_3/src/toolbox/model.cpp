#include "model.h"
#include <iostream>

Model::Model() {

  this->m_Verts = {
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
  this->m_Idxs = {// Front face
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

  glCreateVertexArrays(1, &this->m_Vao);
  glBindVertexArray(this->m_Vao);

  glCreateBuffers(1, &this->m_Vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->m_Vbo);
  glBufferData(GL_ARRAY_BUFFER, this->m_Verts.size() * sizeof(float),
               this->m_Verts.data(), GL_STATIC_DRAW);

  glCreateBuffers(1, &this->m_Ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_Ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               this->m_Idxs.size() * sizeof(unsigned int), this->m_Idxs.data(),
               GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));

  glBindVertexArray(0);

  this->m_ModelUniform = glm::mat4(1.0f);
}

void Model::renderModel() const{

  glBindVertexArray(this->m_Vao);
  std::cout << this->m_Idxs.size() << std::endl;
  glBindVertexArray(0);

}

void Model::setModelLoc()  {

}

void Model::destroyModel() {
  glDeleteBuffers(1, &this->m_Vbo);
  this->m_Vbo = 0;
  glDeleteBuffers(1, &this->m_Ibo);
  this->m_Ibo = 0;
  glDeleteVertexArrays(1, &this->m_Vao);
  this->m_Vao = 0;

}
