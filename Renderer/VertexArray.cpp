#include "VertexArray.hpp"
#include <gl3w.h>
#include <glm.hpp>

VertexArray::VertexArray()
{
	GL(glCreateVertexArrays(1, &m_id));
	GL(glCreateBuffers(1, &m_PositionBuffer));
	GL(glCreateBuffers(1, &m_NormalBuffer));
	GL(glCreateBuffers(1, &m_ColorBuffer));
	GL(glCreateBuffers(1, &m_IndexBuffer));
	
}

VertexArray::~VertexArray()
{
	GL(glDeleteVertexArrays(1, &m_id));
	GL(glDeleteBuffers(1, &m_PositionBuffer));
	GL(glDeleteBuffers(1, &m_NormalBuffer));
	GL(glDeleteBuffers(1, &m_ColorBuffer));
	GL(glDeleteBuffers(1, &m_IndexBuffer));

}

uint32_t VertexArray::ID()
{
	return m_id;
}

uint32_t VertexArray::PositionBuffer()
{
	return m_PositionBuffer;
}

uint32_t VertexArray::NormalBuffer()
{
	return m_NormalBuffer;
}

uint32_t VertexArray::ColorBuffer()
{
	return m_ColorBuffer;
}

uint32_t VertexArray::IndexBuffer()
{
	return m_IndexBuffer;
}

void VertexArray::FillVertexBuffers(size_t vertex_count, glm::vec3 positions[], glm::vec3 normals[], glm::vec3 colors[])
{
	constexpr uint32_t attrib_position = 0u;
	GL(glNamedBufferStorage(m_PositionBuffer, vertex_count*sizeof(glm::vec3), positions, 0));
	GL(glEnableVertexArrayAttrib(m_id, attrib_position));
	GL(glVertexArrayAttribFormat(m_id, attrib_position, 3, GL_FLOAT, GL_FALSE, 0));
	GL(glVertexArrayVertexBuffer(m_id, attrib_position, m_PositionBuffer, 0, sizeof(glm::vec3)));
	GL(glVertexArrayAttribBinding(m_id, attrib_position, attrib_position));

	constexpr uint32_t attrib_normal = 1u;
	GL(glNamedBufferStorage(m_NormalBuffer, vertex_count*sizeof(glm::vec3), normals, 0));
	GL(glEnableVertexArrayAttrib(m_id, attrib_normal));
	GL(glVertexArrayAttribFormat(m_id, attrib_normal, 3, GL_FLOAT, GL_TRUE, 0));
	GL(glVertexArrayVertexBuffer(m_id, attrib_normal, m_NormalBuffer, 0, sizeof(glm::vec3)));
	GL(glVertexArrayAttribBinding(m_id, attrib_normal, attrib_normal));

	constexpr uint32_t attrib_color = 2u;
	GL(glNamedBufferStorage(m_ColorBuffer, vertex_count*sizeof(glm::vec3), colors, 0));
	GL(glEnableVertexArrayAttrib(m_id, attrib_color));
	GL(glVertexArrayAttribFormat(m_id, attrib_color, 3, GL_FLOAT, GL_FALSE, 0));
	GL(glVertexArrayVertexBuffer(m_id, attrib_color, m_ColorBuffer, 0, sizeof(glm::vec3)));
	GL(glVertexArrayAttribBinding(m_id, attrib_color, attrib_color));

}

void VertexArray::FillIndexBuffer(size_t index_count, uint32_t indices[])
{
	GL(glNamedBufferStorage(m_IndexBuffer, index_count*sizeof(uint32_t), indices, 0));
	GL(glVertexArrayElementBuffer(m_id, m_IndexBuffer));

}

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
