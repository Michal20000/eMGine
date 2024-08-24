#include <glfw3.h>
#include "Window.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Time.hpp"

void KeyFunction(GLFWwindow* window, int32_t key, int32_t code, int32_t action, int32_t modifier_bits)
{
	int32_t key_index = key - Keyboard::s_Offset;
	if (action == GLFW_PRESS && Keyboard::IsReleased(key)) {
		Keyboard::s_Keys[key_index] = -Time::s_Before;

	}
	else if (action == GLFW_RELEASE && Keyboard::IsPressed(key)) {
		Keyboard::s_Keys[key_index] = Time::s_Before;

	}

}
void CharacterFunction(GLFWwindow* window, uint32_t character)
{
	Keyboard::s_CharacterTime = Time::s_Before;
	Keyboard::s_Character = character;

}
void MouseLocationFunction(GLFWwindow* window, double location_x, double location_y)
{
	Mouse::s_MotionTime = Time::s_Before;
	Mouse::s_Motion.X = location_x - Mouse::s_Location.X;
	Mouse::s_Motion.Y = location_y - Mouse::s_Location.Y;
	Mouse::s_Location.X = location_x;
	Mouse::s_Location.Y = location_y;

}
void MouseButtonFunction(GLFWwindow* window, int32_t button, int32_t action, int32_t modifier_bits)
{
	if (action == GLFW_PRESS && Mouse::IsReleased(button)) {
		Mouse::s_Buttons[button] = -Time::s_Before;

	}
	else if (action == GLFW_RELEASE && Mouse::IsPressed(button)) {
		Mouse::s_Buttons[button] = Time::s_Before;

	}

}
void MouseEnterFunction(GLFWwindow* window, int32_t is_entered)
{
	Mouse::s_Entered = is_entered ? Time::s_Before : -Time::s_Before;

}
void MouseScrollFunction(GLFWwindow* window, double offset_x, double offset_y)
{
	Mouse::s_ScrollMotionTime = Time::s_Before;
	Mouse::s_ScrollMotion.X = offset_x;
	Mouse::s_ScrollMotion.Y = offset_y;

}



Window::Window(Application& application, const char* title, size_t width, size_t height) :
m_Application(application),
m_Width(width),
m_Height(height)
{
	GLFW(glfwInit());
	GLFW(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4));
	GLFW(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6));
	GLFW(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));

	GLFW(m_Display = glfwGetPrimaryMonitor());
	// TODO: no display
	GLFW(m_Window = glfwCreateWindow(m_Width, m_Height, title, nullptr, nullptr));
	THROW(m_Window == nullptr, GLFWError, "Window should be Created");
	GLFW(glfwMakeContextCurrent(m_Window));
	LOG_WARN("Window is Created"); // TODO: delete

	GLFW(glfwSetKeyCallback(m_Window, &KeyFunction));
	GLFW(glfwSetCharCallback(m_Window, &CharacterFunction));
	GLFW(glfwSetCursorPosCallback(m_Window, &MouseLocationFunction));
	GLFW(glfwSetMouseButtonCallback(m_Window, &MouseButtonFunction));
	GLFW(glfwSetCursorEnterCallback(m_Window, &MouseEnterFunction));
	GLFW(glfwSetScrollCallback(m_Window, &MouseScrollFunction));

	GLFW(glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL));
	// TODO: TRUE or FALSE
	GLFW(glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GLFW_TRUE));
	GLFW(glfwSetInputMode(m_Window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE));

	GLFW(bool is_raw_motion_supported = glfwRawMouseMotionSupported());
	if (is_raw_motion_supported)
		GLFW(glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE));
	GLFW(glfwSetInputMode(m_Window, GLFW_LOCK_KEY_MODS, GLFW_TRUE));

}
Window::~Window()
{
	GLFW(glfwDestroyWindow(m_Window));
	GLFW(glfwTerminate());
	LOG_WARN("Window is Destroyed"); // TODO: delete

}



Application& Window::GetApplication()
{
	return m_Application;

}

size_t Window::Width()
{
	return m_Width;

}
size_t Window::Height()
{
	return m_Height;

}
void Window::EnableCursor()
{
	GLFW(glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL));

}
void Window::DisableCursor()
{
	GLFW(glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));

}



bool Window::IsRunning()
{
	GLFW(bool should_close = glfwWindowShouldClose(m_Window));
	return !should_close;

}
void Window::PollEvents()
{
	GLFW(glfwPollEvents());

}
void Window::Refresh()
{
	GLFW(glfwSwapBuffers(m_Window));

}

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