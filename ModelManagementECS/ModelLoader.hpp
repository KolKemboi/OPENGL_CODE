#pragma once

#include <glad/glad.h>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include "Shader.hpp"


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

	if (!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "ERROR::ASSIMP IMPORTER::" << importer.GetErrorString() << std::endl;
		return Mesh{};
	}


}