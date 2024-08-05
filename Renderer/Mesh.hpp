#pragma once
#include "RendererUtilities.hpp"
#include "VertexArray.hpp"

class Mesh
{
	public:
	Mesh();
	void LoadFromProgram(glm::vec3 positions[], glm::vec3 normals[]);
	void LoadFromProgram(glm::vec3 positions[], glm::vec3 normals[], glm::vec3 colors[]);
	//void LoadFromFile(); //TODO assimp
    VertexArray vertexArray;
    //uint32_t texture;
	//size_t& vertexCount = vertexArray.vertexCount;
    //size_t& indexCount = vertexArray.indexCount;

	private:

};