#pragma once
// FIXME: !!!
#include "EntityEngine/EntityEngine.hpp"
#include <gl3w.h>



class Renderer
{
	public:
	// TODO: 5_RULE
	// TODO: Application&!!!
	Renderer(Application& application);
	~Renderer();

	Application& GetApplication();
	void Pipeline();
	// void SetShader(Shader& shader);

	private:
	Application& m_Application;
	// Shader* m_shader;
	uint32_t m_pipeline;
	// void m_DrawObject(MeshData& mesh_data);

};
