#include "Mesh.hpp"

void Mesh()
{}

void Mesh::LoadFromProgram(glm::vec3 positions[], glm::vec3 normals[], uint32_t indices[])
{
	if (positions == nullptr || normals == nullptr)
	{
		LOG_ERROR("Invalid mesh data to import");
		return;
	}

	VertexCount = sizeof(positions)/sizeof(positions[0]);
	IndexCount = sizeof(indices)/sizeof(indices[0]);
	
	m_VertexArray.FillVertexBuffers(VertexCount, positions, normals, nullptr);
	m_VertexArray.FillIndexBuffer(IndexCount, indices);

}

void Mesh::LoadFromProgram(glm::vec3 positions[], glm::vec3 normals[], glm::vec3 colors[], uint32_t indices[])
{
	if (positions == nullptr || normals == nullptr)
	{
		LOG_ERROR("Invalid mesh data to import");
		return;
	}

	VertexCount = sizeof(positions)/sizeof(positions[0]);
	IndexCount = sizeof(indices)/sizeof(indices[0]);

	m_VertexArray.FillVertexBuffers(VertexCount, positions, normals, colors);
	m_VertexArray.FillIndexBuffer(IndexCount, indices);

}

VertexArray& Mesh::GetVertexArray()
{
	return m_VertexArray;
}

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
