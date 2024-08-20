#include "Renderer.hpp"

#include <gl3w.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "EntityEngine.hpp"
#include "Application.hpp"
#include "Window.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Drawable.hpp"

Renderer::Renderer(Application& application) :
	m_Application(application),
	m_Window(application.GetWindow())
{
	CreatePipeline();

}

Renderer::~Renderer()
{
	DestroyPipeline();

}

Application& Renderer::GetApplication()
{
	return m_Application;

}

// void Renderer::DefaultCameraRender() //TO CHANGE
// {
// 	//TO CHANGE
// 	glm::mat4 modelMatrix = glm::mat4(1.0f);
// 	glm::mat4 projMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>((m_Window->Width())/(m_Window->Height())), 0.1f, 500.0f);
// 	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 5.0f, 0.5f), glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

// }

void Renderer::SetShader(Shader& shader)
{
	m_Shader = &shader;
	m_Shader->Bind(m_Pipeline);

}

void Renderer::OnFrame(EntityEngine& ee, float delta_time)
{
	Application& application = ee.GetApplication();
	Renderer& renderer = application.GetRenderer();
	GL(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
	GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	for (EntityView view = ee.View<Drawable>(); view.Verify(); ++view)
	{
		Entity entity = view.Record();
		Drawable drawable = view.Fragment<Drawable>();
		renderer.DrawObject(drawable);
	}

}

void Renderer::CreatePipeline()
{
	GL(glCreateProgramPipelines(1, &m_Pipeline));

}

void Renderer::DestroyPipeline()
{
	GL(glDeleteProgramPipelines(1, &m_Pipeline));

}

void Renderer::DrawObject(Drawable& drawable)
{
	//TODO CHANGE!!!
	float screen_ratio = static_cast<float>(m_Window.Width()/m_Window.Height());
	glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, -10.f);
	glm::vec3 camera_up_vector = glm::vec3(0.0f, 0.0f, 1.0f);

	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, glm::vec3(-1.0f, -1.0f, -10.0f));
	model_matrix = glm::rotate(model_matrix, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 view_matrix = glm::lookAt(camera_position, camera_target, camera_up_vector);

	glm::mat4 proj_matrix = glm::perspective(glm::radians(50.0f), screen_ratio, 0.1f, 500.0f);

	m_Shader->UploadMVP(proj_matrix*view_matrix*model_matrix);

	Mesh& mesh = drawable.GetMesh();
	VertexArray& vertex_array = mesh.GetVertexArray();
	glBindVertexArray(vertex_array.ID());
	//glBindTextureUnit(unit, texture);
	glDrawElements(GL_TRIANGLES, mesh.IndexCount, GL_UNSIGNED_INT, nullptr);

}

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
