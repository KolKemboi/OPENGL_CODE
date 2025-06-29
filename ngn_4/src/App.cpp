#include <iostream>

struct Model {
  unsigned int idx_count;
  unsigned int vertexArray;
};

Model createModel();

int main() {
  Model model = createModel();
  std::cout << model.idx_count << std::endl;
}

#ifndef gaurd
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

#include <vector>


Model createModel() {
  unsigned int vao = 0, vbo = 0, ibo = 0;

  std::vector<float> verts = {
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
  std::vector<unsigned int> idxs = {// Front face
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

  glCreateVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glCreateBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(),
               GL_STATIC_DRAW);

  glCreateBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxs.size() * sizeof(unsigned int),
               idxs.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));

  glBindVertexArray(0);
  return Model{static_cast<unsigned int>(idxs.size()), vao};
}
