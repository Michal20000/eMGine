#pragma once
#include <cstdint>
#include "Dependencies/GL3W/include/gl3w.h"

class VertexArray
{
    public:
    VertexArray();
    ~VertexArray();
    uint32_t VertexBuffer();
    uint32_t IndexBuffer();
    void AddAttribute(int32_t size, size_t size_of_datatype, GLenum type, size_t relative_offset, bool normalized);
    
    private:
    uint32_t m_id;
    uint32_t m_vertexBuffer;
    uint32_t m_indexBuffer;
    static uint8_t s_attributesCount;
    
};