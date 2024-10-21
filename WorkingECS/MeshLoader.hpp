#pragma once
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <memory>
#include <iostream>
#include <vector>
#include "Shader.hpp"

typedef unsigned int u_int;

struct Vertex {
    glm::vec3 Position, Normal;
};

struct Mesh {
    u_int VAO, VBO, EBO, shaderProgram;
    size_t indexCount;
};

Mesh CreateMesh(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals);

    if (!scene || !scene->mRootNode) {
        std::cerr << "Error loading mesh: " << importer.GetErrorString() << std::endl;
        return {};
    }

    aiMesh* mesh = scene->mMeshes[0];
    std::vector<float> vertices;
    std::vector<u_int> indices;

    for (u_int i = 0; i < mesh->mNumVertices; i++) {
        vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z,
                                          mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z });
    }

    for (u_int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
    }

    Mesh m;
    glGenVertexArrays(1, &m.VAO);
    glGenBuffers(1, &m.VBO);
    glGenBuffers(1, &m.EBO);

    glBindVertexArray(m.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u_int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    Shader shader;
    m.shaderProgram = shader.GetProgram();
    m.indexCount = indices.size();

    std::cout << "Mesh loaded with " << m.indexCount << " indices.\n";
    return m;
}