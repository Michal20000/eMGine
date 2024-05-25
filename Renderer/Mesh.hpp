#pragma once
#include "RendererUtilities.hpp"
#include "VertexArray.hpp"

class Mesh
{
	public:
    VertexArray vertexArray;
    uint32_t& vertexBuffer;
    uint32_t& indexBuffer;
    //texture;
    size_t indexCount;
	void LoadFromProgram(glm::vec3 positions[], glm::vec3 normals[], glm::vec3 colors[]);
	//void LoadFromFile(); //TODO assimp

	private:
	;

};