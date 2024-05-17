#include "./VertexArray.hpp"
#include "./RendererUtilities.hpp"
#include <cstddef>
#include <cstdint>

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &m_id);
}

void VertexArray::AddAttribute(int32_t size, GLenum type, size_t relative_offset, bool normalized)
{
    const uint32_t attribute_location = 0;
    // constexpr uint8_t ATTR_LOC = s_attributesCount;
    glEnableVertexArrayAttrib(m_id, attribute_location);
    glVertexArrayAttribFormat(m_id, attribute_location, size, type, normalized, relative_offset);
    glVertexArrayVertexBuffer(m_id, attribute_location, m_vertexBuffer, relative_offset, sizeof(Vertex)); //TODO
    glVertexArrayAttribBinding(m_id, attribute_location, m_vertexBuffer);
    s_attributesCount++;
}