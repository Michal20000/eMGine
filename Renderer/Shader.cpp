#include "Shader.hpp"
#include <cstdint>

Shader::Shader(const char* vert_filepath, const char* frag_filepath) :
	m_VertexShaderPath(vert_filepath),
	m_FragmentShaderPath(frag_filepath)
{
	CompileVertexShader();
	CompileFragmentShader();
}

Shader::~Shader()
{
	GL(glDeleteProgram(m_VertexShader));
	GL(glDeleteProgram(m_FragmentShader));
}

void Shader::CompileVertexShader()
{
	std::string source = LoadShaderSource(m_VertexShaderPath);
	m_VertexShader = CompileShader(source.c_str(), GL_VERTEX_SHADER, "VS log: ");
}

void Shader::CompileFragmentShader()
{
	std::string source = LoadShaderSource(m_FragmentShaderPath);
	m_FragmentShader = CompileShader(source.c_str(), GL_FRAGMENT_SHADER, "FS log: ");
}

void Shader::Bind(uint32_t pipeline)
{
	GL(glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, m_VertexShader));
	GL(glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, m_FragmentShader));
}

std::string Shader::LoadShaderSource(const char* filepath)
{
	std::ifstream shader_source(filepath, std::ios::ate | std::ios::in);
	const size_t length = shader_source.tellg();
	shader_source.seekg(0);
	std::string shader_str;
	shader_str.resize(length);
	shader_source.read(&shader_str.front(), length);
	return shader_str;
}

uint32_t Shader::CompileShader(const char* source, GLenum stage, const char* message)
{
	uint32_t shader = GL(glCreateShaderProgramv(stage, 1, &source));
	std::string log;
	log.resize(1024);
	GL(glGetProgramInfoLog(shader, log.size(), nullptr, &log.front()));
	char* log_c;
	strcpy(log_c, log.c_str());
	strcat(log_c, message);
	LOG_WARN(log_c);
	return shader;
}