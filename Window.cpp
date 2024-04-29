#include "Window.hpp"
#include <glfw3.h>



Window::Window(const char* title, size_t width, size_t height) :
	m_Width(width),
	m_Height(height)
{
	GLFW(glfwInit());
	GLFW(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4));
	GLFW(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6));
	GLFW(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));

	GLFW(m_Display = glfwGetPrimaryMonitor());
	GLFW(m_Window = glfwCreateWindow(m_Width, m_Height, title, m_Display, nullptr));
	THROW(m_Window == nullptr, GLFWError, "Window should be Created");
	GLFW(glfwMakeContextCurrent(m_Window));
	LOG_WARN("Window is Created");

	// TODO: Callbacks...

}
Window::~Window()
{
	GLFW(glfwDestroyWindow(m_Window));
	GLFW(glfwTerminate());
	LOG_WARN("Window is Destroyed");
}



void Window::Main()
{
	// GLFW(glfwWindowShouldClose(m_Window));
	while (!glfwWindowShouldClose(m_Window)) {
		GLFW(glfwPollEvents());
		GLFW(glfwSwapBuffers(m_Window));
			
	}
	// Main Loop is basically
	// 1. IO like Mouse or Keyboard;
	// 2. Update;
	// 3. Draw;


}
size_t Window::Width()
{
	return m_Width;

}
size_t Window::Height()
{
	return m_Height;

}
// void Window::Width(size_t width)
// {

// }
// void Window::Height(size_t height)
// {

// }





// void Window::Create(uint16_t window_size_x, uint16_t window_size_y, const char* title)
// {
//     glfwInit();
//     // GLFW ERROR;
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
// 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//     m_windowSize = {window_size_x, window_size_y};

//     m_primaryMonitor = glfwGetPrimaryMonitor();
//     m_GLFWwindow = glfwCreateWindow(m_windowSize.width, m_windowSize.height, title, m_primaryMonitor, m_share);
//     if (m_GLFWwindow == nullptr) glfwTerminate();
//     //TODO: throw an exception? //throw std::runtime_error("Failed to recreate window.");
//     glfwMakeContextCurrent(m_GLFWwindow);
// }

// void Window::EnableCursor() 
// {
//     glfwSetInputMode(m_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
// }

// void Window::DisableCursor()
// {
//     glfwSetInputMode(m_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
// }

// void Window::SetWindowSize(uint16_t width, uint16_t height)
// {
//     glfwSetWindowSize(m_GLFWwindow, (int)width, (int)height);
//     m_windowSize = {width, height};
// }

// WindowSize Window::GetWindowSize()
// {
//     int width;
//     int height;
//     glfwGetWindowSize(m_GLFWwindow, &width, &height);
//     m_windowSize = {(uint16_t)width, (uint16_t)height};
//     return m_windowSize;
// }

// void Window::SetFullscreen(bool fullscreen)
// {
//     //TODO
// }

// // void Window::SetCustomCursor(GLFWimage* cursor_image)
// // {
// //     if (m_cursor != nullptr) glfwDestroyCursor(m_cursor);
// //     m_cursor = glfwCreateCursor(cursor_image, 0, 0);
// //     glfwSetCursor(m_GLFWwindow, m_cursor);
// // }

// // void Window::SetStandardCursor(int32_t shape)
// // {
// //     //GLFW_ARROW_CURSOR     == 0x00036001
// //     //GLFW_IBEAM_CURSOR     == 0x00036002
// //     //GLFW_CROSSHAIR_CURSOR == 0x00036003
// //     //GLFW_HAND_CURSOR      == 0x00036004
// //     //GLFW_HRESIZE_CURSOR   == 0x00036005
// //     //GLFW_VRESIZE_CURSOR   == 0x00036006
// //     if (m_cursor != nullptr) glfwDestroyCursor(m_cursor);
// //     m_cursor = glfwCreateStandardCursor(shape);
// //     glfwSetCursor(m_GLFWwindow, m_cursor);
// // }

// GLFWwindow* Window::GetWindowPtr()
// {
//     return m_GLFWwindow;
// }