#pragma once
#include "Dependencies/GL3W/include/gl3w.h"
#include "RendererUtilities.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdint>

class Shader
{
	public:
	Shader(const char* vert_filepath, const char* frag_filepath);
	Shader(const Shader& ob) = delete;
	Shader(Shader&& ob) = delete;
	~Shader();
	friend class Renderer;

	void SetVertexShaderPath(const char* filepath);
	void SetFragmentShaderPath(const char* filepath);
	void CompileVertexShader();
	void CompileFragmentShader();
	void Bind(uint32_t pipeline);

	private:
	const char* m_VertexShaderPath;
	const char* m_FragmentShaderPath;
	uint32_t m_VertexShader;
	uint32_t m_FragmentShader;
	std::string LoadShaderSource(const char* filepath);
	uint32_t CompileShader(const char* source, GLenum stage, const char* message);

};