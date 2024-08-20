#pragma once
#include "Renderer/RendererUtilities.hpp"



class Window
{
	public:
	friend class Application;
	Window(Application& application, const char* title, size_t width, size_t height);
	Window(const Window& ob) = delete;
	Window(Window&& ob) = delete;
	~Window();
	Window& operator=(const Window& ob) = delete;
	Window& operator=(Window&& ob) = delete;
	
	Application& GetApplication();
	// Vector2F Resolution();
	// void Resolution(Vector2F resolution);
	size_t Width();
	size_t Height();

	void EnableCursor();
	void DisableCursor();
	// TODO: cursor_setter

	// TODO: Resize(size_t width, size_t height);
	// void Width(size_t width);
	// void Height(size_t height);
	// TODO: void SetFullscreen(bool fullscreen);


	// EnableCursor DisableCursor HideCursor
	// void EnableCursor();
	// void DisableCursor();
	// Function to Set Cursor...

	private:
	Application& m_Application;
	GLFWwindow* m_Window;
	GLFWmonitor* m_Display;
	GLFWwindow* m_Share = nullptr; // ??? m_Share;
	GLFWcursor* m_Cursor; // ???
	size_t m_Width;
	size_t m_Height;
	// TODO: ...

	bool IsRunning();
	void PollEvents();
	void Refresh();

};
