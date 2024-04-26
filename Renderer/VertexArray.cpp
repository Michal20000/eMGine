#include "./VertexArray.hpp"
#include <cstddef>
#include <cstdint>

inline void VertexArray::Create()
{
    glCreateVertexArrays(1, &m_id);
}

void VertexArray::AddAttribute(int32_t size, GLenum type, bool normalized, uint32_t relative_offset)
{
    static constinit attribute_location = 0;
    // constexpr uint8_t ATTR_LOC = s_attributesCount;
    glEnableVertexArrayAttrib(m_id, ATTR_LOC, size, type, normalized, relative_offset);
    glVertexArrayVertexBuffer(m_id, ATTR_LOC, m_vertexBuffer, offsetof(t, d), sizeof(t)); //TODO
    glVertexArrayAttribBinding(m_id, ATTR_LOC, m_vertexBuffer);
    s_attributesCount++;
}