#pragma once
#include "RendererUtilities.hpp"

class EntityEngine;
class Window;
class Shader;
class Drawable;

class Renderer
{
	public:
	// TODO: 5_RULE
	// TODO: Application&!!!
	Renderer(Application& application);
	~Renderer();

	static void OnFrame(EntityEngine& ee, float delta_time);

	Application& GetApplication();
	uint32_t Pipeline();
	void SetShader(Shader& shader);
	//void SetActiveCamera(Camera& camera);
	//Camera& GetActiveCamera();

	private:
	Application& m_Application;
	Window& m_Window;
	Shader* m_Shader;
	uint32_t m_Pipeline;
	//Camera m_ActiveCamera;
	void CreatePipeline();
	void DestroyPipeline();
	void DrawObject(Drawable& drawable);

};

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
