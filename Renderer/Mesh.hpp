#pragma once
#include <glm.hpp>
#include "RendererUtilities.hpp"
#include "VertexArray.hpp"

class Mesh
{
	public:
	Mesh();

    //uint32_t texture;
	size_t VertexCount;
    size_t IndexCount;

	void LoadFromProgram(glm::vec3 positions[], glm::vec3 normals[], uint32_t indices[]);
	void LoadFromProgram(glm::vec3 positions[], glm::vec3 normals[], glm::vec3 colors[], uint32_t indices[]);
	//void LoadFromFile(); //TODO assimp
	VertexArray& GetVertexArray();

	private:
	VertexArray m_VertexArray;

};

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
