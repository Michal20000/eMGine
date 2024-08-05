#include "Renderer.hpp"



Renderer::Renderer(Application& application) :
	m_Application(application)
{
}

Renderer::~Renderer()
{
}



Application& Renderer::GetApplication()
{
	//TO CHANGE
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 projMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>((m_Window->Width())/(m_Window->Height())), 0.1f, 500.0f);
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 5.0f, 0.5f), glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

}

void Renderer::SetShader(Shader& shader)
{
	m_Shader = &shader;
	m_Shader->Bind(m_Pipeline);

}

void Renderer::OnFrame(EntityEngine& ee, float delta_time)
{
	GL(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
	GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	for (EntityView view = ee.View<MeshData>(); view.Verify(); ++view)
	{
		Entity entity = view.Record();
		MeshData mesh_data = view.Fragment<MeshData>();
		DrawObject(mesh_data);
	}

}