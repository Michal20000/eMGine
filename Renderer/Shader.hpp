#pragma once
#include <cstdint>
#include <string>
#include <glmtypes.hpp>

typedef unsigned int GLenum;

class Shader
{
	public:
	Shader(const char* vert_filepath, const char* frag_filepath);
	Shader(const Shader& ob) = delete;
	Shader(Shader&& ob) = delete;
	~Shader();
	friend bool operator==(const Shader& lob, const Shader& rob);
	friend class Renderer;

	void SetVertexShaderPath(const char* filepath);
	void SetFragmentShaderPath(const char* filepath);
	void CompileVertexShader();
	void CompileFragmentShader();

	private:
	const char* m_VertexShaderPath;
	const char* m_FragmentShaderPath;
	uint32_t m_VertexShader;
	uint32_t m_FragmentShader;
	int32_t m_MVPMatrixLocation;
	std::string LoadShaderSource(const char* filepath);
	uint32_t CompileShader(const char* source, GLenum stage, const char* message);
	void Bind(uint32_t pipeline);
	void UploadMVP(glm::mat4& mvp_matrix);

};

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
