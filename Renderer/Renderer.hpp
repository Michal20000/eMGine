#pragma once
#include "Dependencies/GL3W/include/gl3w.h"
#include "EntityEngine/EntityEngine.hpp"
#include "Shader.hpp"
#include "MeshData.hpp"

class Renderer
{
	public:
	Renderer();
	~Renderer();
	void Pipeline();
	void SetShader(Shader& shader);
	void OnFrame(EntityEngine& ee, float delta_time);
	//void DrawTerrain();

	private:
	Shader* m_shader;
	uint32_t m_pipeline;
	void m_DrawObject(MeshData& mesh_data);
	;

};