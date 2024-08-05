#pragma once
#include <cstdint>
#include "RendererUtilities.hpp"
#include "Dependencies/GL3W/include/gl3w.h"

class VertexArray
{
    public:
	VertexArray();
	~VertexArray();
	uint32_t PositionBuffer();
	uint32_t NormalBuffer();
	uint32_t ColorBuffer();
	uint32_t IndexBuffer();
	void FillVertexBuffers(glm::vec3 positions[], glm::vec3 normals[], glm::vec3 colors[]);
	void FillIndexBuffer(uint32_t indices[]);
	size_t VertexCount;
	size_t IndexCount;

	private:
	uint32_t m_id;
	uint32_t m_PositionBuffer;
	uint32_t m_NormalBuffer;
	uint32_t m_ColorBuffer; //aka coordBuffer 
	uint32_t m_IndexBuffer;

};