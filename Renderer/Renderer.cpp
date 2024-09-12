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
	//gl3w/OpenGL initialisation
	if (gl3wInit())
		LOG_WARN("OpenGL failed to initialise");
	else
	{
		LOG_WARN("OpenGL initialised");
		LOG_WARN(glGetString(GL_VERSION));
		LOG_WARN(glGetString(GL_SHADING_LANGUAGE_VERSION));
	}

	if (!gl3wIsSupported(4, 6))
		LOG_WARN("OpenGL version 4.6 not supported");

	//OpenGL config
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//pipeline creation
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
	LOG_SILLY("Shader " << m_Shader << " set");

}

void Renderer::OnFrame(EntityEngine& ee, float delta_time)
{
	Application& application = ee.GetApplication();
	Renderer& renderer = application.GetRenderer();
	GL(glClearColor(0.5f, 0.0f, 0.5f, 1.0f));
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
	glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, -10.0f);
	glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 camera_up = glm::vec3(0.0f, 0.0f, 1.0f); //Z-up

	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, glm::vec3(-1.0f, -1.0f, 0.0f));
	model_matrix = glm::rotate(model_matrix, glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 view_matrix = glm::lookAt(camera_position, camera_target, camera_up);

	glm::mat4 proj_matrix = glm::perspective(glm::radians(50.0f), screen_ratio, 0.1f, 500.0f);

	glm::mat4 mvp_matrix = proj_matrix*view_matrix*model_matrix;

	m_Shader->UploadMVP(mvp_matrix);

	Mesh& mesh = drawable.GetMesh();
	VertexArray& vertex_array = mesh.GetVertexArray();
	GL(glBindVertexArray(vertex_array.ID()));
	//glBindTextureUnit(unit, texture);
	GL(glDrawElements(GL_TRIANGLES, mesh.IndexCount, GL_UNSIGNED_INT, nullptr));

}

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
