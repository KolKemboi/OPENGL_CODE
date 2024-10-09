#pragma once

#include <glad/glad.h>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

typedef unsigned int u_int;


struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
};

class Mesh
{
public:
	std::vector <Vertex> m_Vertices;
	std::vector <unsigned int> m_Indices;
	u_int m_Vao;
	Mesh(std::vector <Vertex> vertices, std::vector<u_int> indices)
	{

	}
	void MeshDestroyer()
	{

	}
	void DrawMesh()
	{

	}

private:
	u_int m_Vbo, m_Ebo;

};

class ModelLoader
{
public:
	ModelLoader();
	
	void LoadMesh(std::string const& fileName)
	{

	}

private:
	void ProcessNode(aiNode* node, const aiScene* scene)
	{

	}
	Mesh ProcessMesh(aiNode* mesh, const aiScene* scene)
	{

	}

};