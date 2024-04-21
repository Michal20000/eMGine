#ifndef SHADER_H
#define SHADER_H

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

#endif