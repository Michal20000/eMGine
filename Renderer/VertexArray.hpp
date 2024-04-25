#pragma once
#include <cstdint>

class VertexArray
{
public:
    inline void Create();
    void AddAttribute(int32_t size, GLenum type, bool normalized, uint32_t relative_offset);
private:
    uint32_t m_id;
    uint32_t m_vertexBuffer;
    static uint8_t s_attributesCount;
};