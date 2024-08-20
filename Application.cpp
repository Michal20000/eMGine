#include "Application.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "EntityEngine.hpp"
#include "Time.hpp"

Application::Application()
{
	m_Window = new Window(*this, "eMGine", 1280, 720);
	m_Renderer = new Renderer(*this);
	m_EntityEngine = new EntityEngine(*this);

	// TODO: configurations...
	// TODO: EntityEngine::Register<...>();

}
Application::~Application()
{
	delete m_Window;
	delete m_Renderer;
	delete m_EntityEngine;

}



// TODO: delete this shit
#include <windows.h>
#include <glm.hpp>
#include "Keyboard.hpp"
#include "Mouse.hpp"

#include "Renderer.hpp"
#include "Renderer/Mesh.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/BasicShapes.hpp"
// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
// COLUMN  COLUMN  COLUMN    COLUMN

void Application::Main()
{
	EntityEngine& ee = this->GetEntityEngine();

	glm::mat4 test_matrix = {
		{ 0.0, 1.0, 2.0, 3.0 },
		{ 0.0, 1.0, 2.0, 3.0 },
		{ 0.0, 1.0, 2.0, 3.0 },
		{ 0.0, 1.0, 2.0, 3.0 }
	};
	float* pointer_test_matrix = (float*)&test_matrix;
	for (uint64_t i = 0; i < 16; ++i)
		LOG_SILLY(i <<" : "<< *(pointer_test_matrix + i));

	;

	Shader* shader_d = new Shader("Resources/default_vert.glsl", "Resources/default_frag.glsl");

	EntityEngine::Register<Renderer>();
	
	ee.Dispatch<BasicShapes::CreateCubeEvent>();
	ee.OnEvent();

	float delta_time = 0.0f;

	while (m_Window->IsRunning()) {
		// TODO: dt calculations...
		uint64_t before = Time::Now();
		Time::s_Before = before;
		// ...for IO calculations

		m_Window->PollEvents();

		// TODO: m_Window.OnFrame();
		// TODO: m_EntityEngine.OnPeriodic();
		// TODO: m_EntityEngine.OnFrame();
		if (Mouse::IsPressed(LEFT_MOUSE_BUTTON) && Mouse::Duration(LEFT_MOUSE_BUTTON) == 0.0F) m_Window->DisableCursor();
		if (Mouse::IsReleased(LEFT_MOUSE_BUTTON) && Mouse::Duration(LEFT_MOUSE_BUTTON) == 0.0F) m_Window->EnableCursor();

		Vector2F location =  Mouse::Location();
		Vector2F motion = Mouse::Motion();
		if (Mouse::IsPressed(RIGHT_MOUSE_BUTTON)) {
			LOG_SILLY("Location is " << location.X << " " << location.Y);
			LOG_SILLY("Motion is " << motion.X << " " << motion.Y);
		}

		if (Mouse::HasEntered()) LOG_FL_SILLY("has_entered");
		if (Mouse::HasLeft()) LOG_FL_SILLY("has_left");


		// if (Keyboard::IsPressed(KEY_A) && Keyboard::Duration(KEY_A) == 0.0F) LOG("A Press");
		// if (Keyboard::IsReleased(KEY_A) && Keyboard::Duration(KEY_A) == 0.0F) LOG("A Release");
		// if (Keyboard::IsCharacter()) std::cout << Keyboard::Character();

		// TODO: Mouse::
		// ...loc.X loc.Y change.X change.Y
		// ...wheel?
		// ...LMB MMB RMB
		// platform_thread(); platform_file();
		// platform_wait(); platform_now();
		// platform_vreserve(); platform_vfree();

		// TODO: Keyboard::Character('a');
		// TODO: Keyboard::IsCharacter();

		m_EntityEngine->OnFrame(delta_time);

		Sleep(10);

		// TODO: global_events Like change_level
		
		uint64_t after = Time::Now();
		delta_time = Time::Duration(before, after);
		// TODO: Delete!
		// TODO: Dt calculations...
		// LOG_SILLY("Duration " << duration << "s");

		m_Window->Refresh();

	}

	delete shader_d;

}
// {
// 	while (true) {
// 		// dt = 0.0F;
// 		// before = Time::Now();
// 		// IDEA: OnPeriodic; LIMIT 50FPS;
// 		// IDEA: OnFrame; LIMIT 200FPS or LIMITLESS;
// 		// after = Time::Now();
// 		// dt = Time::Duration<float>(before, after);
// 			dt = Time::Duration<double>(before, after);
// 		// IDEA: if dt > fpsDt: Wait;
// 		// IDEA: fpsPeriodic <= fpsFrame;

			
// 	}

// TODO: class GLFWError;
// TODO: class GLError;
// TODO: class GLMError;
// TODO: class STBIError;



// 	// Main Loop is basically
// 	// 1. IO like Mouse or Keyboard;
// 	// 2. Periodic and Frame;
// 	// 3. Frame::Draw; -> std::this_thread::sleap();
// 	// 

// }

Window& Application::GetWindow()
{
	return *m_Window;

}
Renderer& Application::GetRenderer()
{
	return *m_Renderer;

}
EntityEngine& Application::GetEntityEngine()
{
	return *m_EntityEngine;

}
