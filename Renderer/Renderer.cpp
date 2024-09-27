#include "Renderer.hpp"

#include <gl3w.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
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
	GL(glEnable(GL_DEPTH_TEST));
	GL(glDepthFunc(GL_LESS));
	GL(glEnable(GL_CULL_FACE));
	GL(glFrontFace(GL_CCW));
	//GL(glEnable(GL_BLEND));
	//GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

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

}

void Renderer::OnFrame(EntityEngine& ee, float delta_time)
{
	Application& application = ee.GetApplication();
	Renderer& renderer = application.GetRenderer();
	Window& window = application.GetWindow();

	GL(glClearColor(0.5f, 0.0f, 0.5f, 1.0f));
	GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	float screen_ratio = static_cast<float>(window.Width())/static_cast<float>(window.Height());
	glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::vec3 camera_target = glm::vec3(-0.5f, -0.5f, 0.0f);
	glm::vec3 camera_up = glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)); //Z-up

	glm::mat4 view_matrix = glm::lookAt(camera_position, camera_target, camera_up);

	glm::mat4 proj_matrix = glm::perspective(glm::radians(60.0f), screen_ratio, 0.1f, 1000.0f);

	for (EntityView view = ee.View<Drawable>(); view.Verify(); ++view)
	{
		Entity entity = view.Record();
		Drawable drawable = view.Fragment<Drawable>();
		renderer.DrawObject(drawable, view_matrix, proj_matrix);
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

void Renderer::DrawObject(Drawable& drawable, glm::mat4& view_matrix, glm::mat4& proj_matrix)
{
	//TODO CHANGE!!!
	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, glm::vec3(-1.0f, -1.0f, 0.0f));
	model_matrix = glm::rotate(model_matrix, glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model_matrix = glm::rotate(model_matrix, glm::radians(25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	glm::mat4 mvp_matrix = proj_matrix*view_matrix*model_matrix;
	m_Shader->UploadMVP(mvp_matrix);

	GL(glBindProgramPipeline(m_Pipeline));
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
