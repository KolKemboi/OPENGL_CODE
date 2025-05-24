#pragma once

#include <glad/glad.h>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include "Shader.hpp"
#include <iostream>

typedef unsigned int u_int;

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
};

struct Mesh
{
    u_int vertexArray;
    u_int vertexBuffer;
    u_int indexBuffer;
    u_int shader;
    size_t indexCount;
};

Mesh CreateMesh(const std::string& modelPath)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals);

    if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP IMPORTER::" << importer.GetErrorString() << std::endl;
        return Mesh{};
    }

    aiMesh* mesh = scene->mMeshes[0];
    std::vector<float> vertices;
    std::vector<u_int> indices;

    for (u_int i = 0; i < mesh->mNumVertices; i++)
    {
        aiVector3D pos = mesh->mVertices[i];
        aiVector3D norm = mesh->mNormals[i];

        // Add position data
        vertices.push_back(pos.x);
        vertices.push_back(pos.y);
        vertices.push_back(pos.z);

        // Add normal data
        vertices.push_back(norm.x);
        vertices.push_back(norm.y);
        vertices.push_back(norm.z);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    Mesh loadedMesh;

    // Generate and bind the vertex array
    glGenVertexArrays(1, &loadedMesh.vertexArray);
    glBindVertexArray(loadedMesh.vertexArray);

    // Generate and bind the vertex buffer
    glGenBuffers(1, &loadedMesh.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, loadedMesh.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Generate and bind the index buffer
    glGenBuffers(1, &loadedMesh.indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, loadedMesh.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u_int), indices.data(), GL_STATIC_DRAW);

    // Define the vertex attributes (positions and normals)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Normals
    glEnableVertexAttribArray(1);

    // Unbind the vertex array
    glBindVertexArray(0);

    // Load shader (assuming Shader class is correctly defined elsewhere)
    Shader modshader;
    loadedMesh.shader = modshader.RetShaderProgram();
    loadedMesh.indexCount = indices.size();

    std::cout << "Mesh loaded successfully with " << loadedMesh.indexCount << " indices." << std::endl;
    return loadedMesh;
}
