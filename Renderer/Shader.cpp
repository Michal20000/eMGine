#include "./Shader.hpp"
#include <cstdint>

inline void Shader::SetVertexShaderPath(const char* filepath)
{
    m_vertexShaderPath = filepath;
}

inline void Shader::SetFragmentShaderPath(const char* filepath)
{
    m_fragmentShaderPath = filepath;;
}

void Shader::SetVertexShader()
{
    std::string source = LoadShaderSource(m_vertexShaderPath);
    m_vertexShader = CompileShader(source, GL_VERTEX_SHADER, "VS log: ");
}

void Shader::SetFragmentShader()
{
    std::string source = LoadShaderSource(m_fragmentShaderPath);
    m_fragmentShader = CompileShader(source, GL_FRAGMENT_SHADER, "FS log: ");
}

void Shader::Bind(uint32_t pipeline)
{
    glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, v_shader);
	glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, f_shader);
}