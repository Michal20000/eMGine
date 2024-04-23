#include "./shader_utils.hpp"
#include <cstdint>

std::string LoadShaderSource(std::string filepath)
{
    std::ifstream shaderSource(filepath, std::ios::ate | std::ios::in);
    const size_t length = shaderSource.tellg();
    shaderSource.seekg(0);
    std::string shader;
    shader.resize(length);
    shaderSource.read(&shader.front(), length);
    return shader;
}

uint32_t CompileShader(const char* source, GLenum stage, const std::string& message)
{
    uint32_t shader = glCreateShaderProgramv(stage, 1, &source);
    std::string log;
    log.resize(1024);
    glGetProgramInfoLog(shader, log.size(), nullptr, &log.front());
    printf("%s: %s\n", message.c_str(), log.c_str());
    return shader;
}