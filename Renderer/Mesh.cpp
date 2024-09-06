#include "Mesh.hpp"

Mesh::Mesh()
{}

Mesh::~Mesh()
{}

void Mesh::LoadFromProgram(
	size_t vertex_count,
	glm::vec3 positions[],
	glm::vec3 normals[],
	size_t index_count,
	uint32_t indices[])
{
	if (positions == nullptr || normals == nullptr)
	{
		LOG_ERROR("Invalid mesh data to import");
		return;
	}

	VertexCount = vertex_count;
	IndexCount = index_count;
	
	m_VertexArray.FillVertexBuffers(VertexCount, positions, normals, nullptr);
	m_VertexArray.FillIndexBuffer(IndexCount, indices);

}

void Mesh::LoadFromProgram(
	size_t vertex_count,
	glm::vec3 positions[],
	glm::vec3 normals[],
	glm::vec3 colors[],
	size_t index_count,
	uint32_t indices[])
{
	if (positions == nullptr || normals == nullptr)
	{
		LOG_ERROR("Invalid mesh data to import");
		return;
	}

	VertexCount = vertex_count;
	IndexCount = index_count;
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
