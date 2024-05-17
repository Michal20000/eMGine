#pragma once
#include "RendererUtilities.hpp"
#include <cstddef>

// struct WindowSize
// {
//     uint16_t width;
//     uint16_t height;
// };

// TODO: class GLFWError;
// TODO: class GLError;
// TODO: class GLMError;
// TODO: class STBIError;

class Window
{
	public:
	Window(const char* title, size_t width, size_t height);
	Window(const Window& ob) = delete;
	Window(Window&& ob) = delete;
	~Window();
	Window& operator=(const Window& ob) = delete;
	Window& operator=(Window&& ob) = delete;
	
    void Main();
	size_t Width();
	size_t Height();
    // TODO: Resize(size_t width, size_t height);
    // void Width(size_t width);
    // void Height(size_t height);
    // TODO: void SetFullscreen(bool fullscreen);

    // ERROR: void Create(uint16_t window_size_x, uint16_t window_size_y, const char* title);
    // void EnableCursor();
    // void DisableCursor();
    // TODO: void SetCustomCursor();
    // TODO: void SetStandardCursor();
    // ERROR: void SetWindowSize(uint16_t width, uint16_t height);
    // ERROR: WindowSize GetWindowSize();
    // ERROR: GLFWwindow* GetWindowPtr();

	private:
	GLFWwindow* m_Window;
	GLFWmonitor* m_Display;
	GLFWwindow* m_Share = nullptr; // ??? m_Share;
	GLFWcursor* m_Cursor; // ???
	size_t m_Width;
	size_t m_Height;

    // TODO: ...
};
