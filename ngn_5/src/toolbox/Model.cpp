#include "Model.hpp"
#include "Shader.hpp"
#include <iostream>
#include <memory>

Model::Model() {

  this->m_Vertdata = {
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
  this->m_Idxdata = {// Front face
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

  // make the VAO, VBO, IBO
	glGenVertexArrays(1, &this->m_Vao);
	glBindVertexArray(this->m_Vao);

	glGenBuffers(1, &this->m_Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_Vbo);
	glBufferData(GL_ARRAY_BUFFER, this->m_Vertdata.size()* sizeof(float), this->m_Vertdata.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &this->m_Ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_Ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_Idxdata.size()* sizeof(unsigned int), this->m_Idxdata.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	this->m_Shader = std::make_shared<Shader>();
}

void Model::renderModel() {
  // bind the vao, bind the shader, render, unbind the shader
	std::cout << this->m_Idxdata.size() << std::endl;
	std::cout << this->m_Shader->retShader() << std::endl;

	this->m_Shader->useShaderProg();
	glBindVertexArray(this->m_Vao);
	glDrawElements(GL_TRIANGLES, this->m_Idxdata.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Model::DestroyModel() {
	this->m_Shader->destroyShader();
  glDeleteVertexArrays(1, &this->m_Vao);
  glDeleteBuffers(1, &this->m_Vbo);
  glDeleteBuffers(1, &this->m_Ibo);
  this->m_Vao = 0;
  this->m_Vbo = 0;
  this->m_Ibo = 0;
}
