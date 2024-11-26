#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <gl3w.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "RendererUtilities.hpp"

Shader::Shader(const char* vert_filepath, const char* frag_filepath) :
	m_VertexShaderPath(vert_filepath),
	m_FragmentShaderPath(frag_filepath),
	m_MVPMatrixLocation(0)
{
	CompileVertexShader();
	CompileFragmentShader();

	GL(m_MVPMatrixLocation = glGetUniformLocation(m_VertexShader, "mvpMatrix"));
	if (m_MVPMatrixLocation == -1)
		LOG_ERROR("MVP matrix location not found in shader");
	else
		LOG_SILLY("MVP matrix location is " << m_MVPMatrixLocation);

	GL(m_ModelMatrixLocation = glGetUniformLocation(m_VertexShader, "modelMatrix"));
	if (m_ModelMatrixLocation == -1)
		LOG_ERROR("Model matrix location not found in shader");
	else
		LOG_SILLY("Model matrix location is " << m_ModelMatrixLocation);

	GL(m_NormalMatrixLocation = glGetUniformLocation(m_VertexShader, "normalMatrix"));
	if (m_NormalMatrixLocation == -1)
		LOG_ERROR("Normal matrix location not found in shader");
	else
		LOG_SILLY("Normal matrix location is " << m_NormalMatrixLocation);

	GL(m_CameraPositionLocation = glGetUniformLocation(m_FragmentShader, "cameraPosition"));
	if (m_CameraPositionLocation == -1)
		LOG_ERROR("MVP matrix location not found in shader");
	else
		LOG_SILLY("MVP matrix location is " << m_CameraPositionLocation);

}

Shader::~Shader()
{
	GL(glDeleteProgram(m_VertexShader));
	GL(glDeleteProgram(m_FragmentShader));

}

bool operator==(const Shader& lob, const Shader& rob)
{
	return (lob.m_VertexShader == rob.m_VertexShader &&
			lob.m_FragmentShader == rob.m_FragmentShader)
			? true : false;

}

void Shader::CompileVertexShader()
{
	std::string source = LoadShaderSource(m_VertexShaderPath);
	m_VertexShader = CompileShader(source.c_str(), GL_VERTEX_SHADER, "Vertex shader log: ");

}

void Shader::CompileFragmentShader()
{
	std::string source = LoadShaderSource(m_FragmentShaderPath);
	m_FragmentShader = CompileShader(source.c_str(), GL_FRAGMENT_SHADER, "Fragment shader log: ");

}

std::string Shader::LoadShaderSource(const char* filepath)
{
	std::ifstream shader_source(filepath, std::ios::ate | std::ios::in);
	shader_source.seekg(0, std::ios_base::end);
	const size_t length = shader_source.tellg();
	shader_source.seekg(0, std::ios_base::beg);
	std::string shader_str;
	shader_str.resize(length + 1);
	shader_source.read(&shader_str.front(), length);
	shader_source.close();
	return shader_str;

}

uint32_t Shader::CompileShader(const char* source, GLenum stage, const char* message)
{
	GL(uint32_t shader = glCreateShaderProgramv(stage, 1, &source));
	std::string log;
	log.resize(1024);
	GL(glGetProgramInfoLog(shader, log.size(), nullptr, &log.front()));
	log = std::string(message).append(" ").append(log);
	LOG_WARN(log.c_str());
	return shader;

}

void Shader::Bind(uint32_t pipeline)
{
	GL(glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, m_VertexShader));
	GL(glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, m_FragmentShader));

	int32_t link_status;
	int32_t info_log_length;

	GL(glGetProgramiv(m_VertexShader, GL_LINK_STATUS, &link_status));
	if (link_status == GL_FALSE)
	{
		GL(glGetProgramiv(m_VertexShader, GL_INFO_LOG_LENGTH, &info_log_length));
		char info_log[info_log_length];
		GL(glGetProgramInfoLog(m_VertexShader, info_log_length, NULL, info_log));
		LOG_ERROR("Vertex shader program Link error: " << info_log);
		
	}
	else
		LOG_SILLY("Vertex shader program linked correctly");

	GL(glGetProgramiv(m_FragmentShader, GL_LINK_STATUS, &link_status));
	if (link_status == GL_FALSE)
	{	
		GL(glGetProgramiv(m_FragmentShader, GL_INFO_LOG_LENGTH, &info_log_length));
		char info_log[info_log_length];
		GL(glGetProgramInfoLog(m_FragmentShader, info_log_length, NULL, info_log));
		LOG_ERROR("Fragment shader program Link error: " << info_log);

	}
	else
		LOG_SILLY("Fragment shader program linked correctly");

}

void Shader::UploadUniforms(
	glm::mat4& mvp_matrix,
	glm::mat4& model_matrix,
	glm::mat3& normal_matrix,
	glm::vec3& camera_position)
{
	GL(glProgramUniformMatrix4fv(m_VertexShader, m_MVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(mvp_matrix)));
	GL(glProgramUniformMatrix4fv(m_VertexShader, m_ModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(model_matrix)));
	GL(glProgramUniformMatrix3fv(m_VertexShader, m_NormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normal_matrix)));
	GL(glProgramUniform3fv(m_FragmentShader, m_CameraPositionLocation, 1, glm::value_ptr(camera_position)));

}

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
