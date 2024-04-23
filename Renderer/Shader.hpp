#pragma once
#include "./utils/shader_utils.hpp"
#include <cstdint>
class Shader
{
private:
    const char* m_vertexShaderPath;
    const char* m_fragmentShaderPath;
    uint32_t m_vertexShader;
    uint32_t m_fragmentShader;
public:
    friend class Renderer;
    Shader();
    ~Shader();
    inline void SetVertexShaderPath(const char* filepath);
    inline void SetFragmentShaderPath(const char* filepath);
    void SetVertexShader();
    void SetFragmentShader();
    void Bind(uint32_t pipeline);
};