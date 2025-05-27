#include "model.h"
#include <iostream>

void Model::makeModel() {
  this->verts = {
      -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
  };
  this->idxs = {
      0,
      1,
      2,
  };
}

void Model::renderModel() {
  std::cout << this->verts.size() << std::endl;
  std::cout << this->idxs.size() << std::endl;
}
