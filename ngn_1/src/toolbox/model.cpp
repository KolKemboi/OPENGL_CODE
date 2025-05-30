#include "model.h"
#include "shader.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

#include <memory>

// TODO: make the VAO, VBO, IBO for all of them, add a basic shader

void Model::makeModel() {

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
  glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(),
               GL_STATIC_DRAW);

  glCreateBuffers(1, &this->m_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxs.size() * sizeof(unsigned int),
               idxs.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));

  glBindVertexArray(0);

  this->m_Shader = std::make_shared<Shader>();
  model = glm::rotate(model, glm::radians(40.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Model::renderModel() {
  // your existing code for view/projection setup
  view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);

  this->m_Shader->activateShader();

  int modelLoc = glGetUniformLocation(this->m_Shader->m_Shader, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

  int viewLoc = glGetUniformLocation(this->m_Shader->m_Shader, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

  int projLoc = glGetUniformLocation(this->m_Shader->m_Shader, "projection");
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

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
