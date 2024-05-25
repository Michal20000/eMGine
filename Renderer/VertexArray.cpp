#include "VertexArray.hpp"
#include "RendererUtilities.hpp"
#include <cstddef>

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &m_id);
		
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_id);
	
}

uint32_t VertexArray::VertexBuffer()
{
	return m_vertexBuffer;
}

uint32_t VertexArray::IndexBuffer()
{
	return m_indexBuffer;
}

void VertexArray::AddAttribute(int32_t size, size_t size_of_datatype, GLenum type, size_t relative_offset, bool normalized)
{
	const uint32_t attribute_location = s_attributesCount;
	// constexpr uint8_t ATTR_LOC = s_attributesCount;
	glEnableVertexArrayAttrib(m_id, attribute_location);
	glVertexArrayAttribFormat(m_id, attribute_location, size, type, normalized, relative_offset);
	glVertexArrayVertexBuffer(m_id, attribute_location, m_vertexBuffer, relative_offset, size_of_datatype); //TODO
	glVertexArrayAttribBinding(m_id, attribute_location, m_vertexBuffer);
	s_attributesCount++;

}