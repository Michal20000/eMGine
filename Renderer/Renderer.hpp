#pragma once
#include "GL3W/include/gl3w.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "EntityEngine/EntityEngine.hpp"
#include "Window.hpp"
#include "Shader.hpp"
#include "MeshData.hpp"

class Renderer
{
	public:
	Renderer(Window* window);
	~Renderer();
	void Pipeline();
	void SetShader(Shader& shader);
	void OnFrame(EntityEngine& ee, float delta_time);
	//void DrawTerrain();

	private:
	Shader* m_Shader;
	Window* m_Window;
	uint32_t m_Pipeline;
	void DrawObject(MeshData& mesh_data);
	;

};