#pragma once
#include <cstdint>
#include "Dependencies/GL3W/include/gl3w.h"

class VertexArray
{
    public:
    VertexArray();
    void AddAttribute(int32_t size, GLenum type, size_t relative_offset, bool normalized);
    private:
    uint32_t m_id;
    uint32_t m_vertexBuffer;
    static uint8_t s_attributesCount;
};