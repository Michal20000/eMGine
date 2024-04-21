#pragma once
#include "./utils/shader_utils.hpp"
class Shader
{
    Shader();
    ~Shader();
    friend class Renderer;
    bool VertexShader();
    bool FragmentShader();
    static bool Bind();
};