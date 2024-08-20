#pragma once
#include <glmtypes.hpp>
#include "RendererUtilities.hpp"

class VertexArray
{
    public:
	VertexArray();
	~VertexArray();
	uint32_t ID();
	uint32_t PositionBuffer();
	uint32_t NormalBuffer();
	uint32_t ColorBuffer();
	uint32_t IndexBuffer();
	void FillVertexBuffers(size_t vertex_count, glm::vec3 positions[], glm::vec3 normals[], glm::vec3 colors[]);
	void FillIndexBuffer(size_t index_count, uint32_t indices[]);
	//TODO change of glm::vec3

	private:
	uint32_t m_id;
	uint32_t m_PositionBuffer;
	uint32_t m_NormalBuffer;
	uint32_t m_ColorBuffer; //aka coordBuffer 
	uint32_t m_IndexBuffer;

};

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
