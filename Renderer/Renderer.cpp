#include "Renderer.hpp"

Renderer::Renderer(Window* window) :
	m_Window(window)
{
	if (!gl3wIsSupported(4, 6))
	{
		LOG_ERROR("OpenGL 4.6 is not available on this computer.");
		window->Terminate();

	}

	if (gl3wInit())
	{
		LOG_ERROR("Failed to initialize OpenGL");
		window->Terminate();

	}

	GL(glCreateProgramPipelines(1, &m_Pipeline));

	if (m_Shader == nullptr)
	{
		m_Shader = new Shader("Resources/default_vert.glsl", "Resources/default_frag.glsl");
	}

	m_Shader->CompileVertexShader();
	m_Shader->CompileFragmentShader();
	m_Shader->Bind(m_Pipeline);

}

Renderer::~Renderer()
{
	if (m_Shader != nullptr)
	{
		delete m_Shader;
	}

}

void Renderer::DrawObject(MeshData& mesh_data)
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