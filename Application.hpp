#pragma once
#include <cstdint>

class Window;
class Renderer;
class EntityEngine;



class Application
{
	public:
	Application();
	Application(const Application& ob) = delete;
	Application(Application&& ob) = delete;
	Application& operator=(const Application& ob) = delete;
	Application& operator=(Application&& ob) = delete;
	~Application();
	void Main();

	private:
	Window* m_Window;
	Renderer* m_Renderer;
	EntityEngine* m_EntityEngine;

	// TODO: !!!
	// m_FrameLimit;
	// m_PeriodicLimit;
	// FrameLimit;
	// PeriodicLimit;

};
