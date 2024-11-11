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

struct _Mesh
{
	u_int vertexArray;
	u_int vertexBuffer;
	u_int indexBuffer;
	u_int shader;
	size_t indexCount;
};

_Mesh CreateMesh(const std::string& modelPath)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals);

	if (!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "ERROR::ASSIMP IMPORTER::" << importer.GetErrorString() << std::endl;
		return _Mesh{};
	}
	aiMesh* mesh = scene->mMeshes[0];
	std::vector<float> vertices;
	std::vector<u_int> indices;

	for (u_int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(pos.x);
		vertices.push_back(pos.y);
		vertices.push_back(pos.z);

	}


    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    _Mesh loadedMesh;

    glGenVertexArrays(1, &loadedMesh.vertexArray);
    glBindVertexArray(loadedMesh.vertexArray);

    glGenBuffers(1, &loadedMesh.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, loadedMesh.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &loadedMesh.indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, loadedMesh.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // Texture Coords
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    Shader modshader;
    loadedMesh.shader = modshader.RetShaderProgram();
    loadedMesh.indexCount = indices.size();
    std::cout << "Out" << std::endl;
    return loadedMesh;
}



