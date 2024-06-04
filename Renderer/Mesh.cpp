#include "Dependencies/GL3W/include/gl3w.h"
#include "Mesh.hpp"

void Mesh::LoadFromProgram(glm::vec3 positions[], glm::vec3 normals[])
{
	if (positions == nullptr || normals == nullptr)
	{
		LOG_ERROR("Invalid mesh data to import");
		return;

	}
	
	vertexArray.FillVertexBuffers(positions, normals, nullptr);

}

void Mesh::LoadFromProgram(glm::vec3 positions[], glm::vec3 normals[], glm::vec3 colors[])
{
	if (positions == nullptr || normals == nullptr)
	{
		LOG_ERROR("Invalid mesh data to import");
		return;

	}

	vertexArray.FillVertexBuffers(positions, normals, colors);

}