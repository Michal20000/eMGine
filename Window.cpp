#include "./Window.hpp"
#include <cstdint>

void Window::Create(uint16_t window_size_x, uint16_t window_size_y, const char* title)
{
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_windowSize = {window_size_x, window_size_y};
    m_primaryMonitor = glfwGetPrimaryMonitor();
    m_GLFWwindow = glfwCreateWindow(m_windowSize.width, m_windowSize.height, title, m_primaryMonitor, m_share);
    if (m_GLFWwindow == nullptr) glfwTerminate();
    //TODO: throw an exception? //throw std::runtime_error("Failed to recreate window.");
    glfwMakeContextCurrent(m_GLFWwindow);
}

void Window::EnableCursor() 
{
    glfwSetInputMode(m_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::DisableCursor()
{
    glfwSetInputMode(m_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::SetWindowSize(uint16_t width, uint16_t height)
{
    glfwSetWindowSize(m_GLFWwindow, (int)width, (int)height);
    m_windowSize = {width, height};
}

WindowSize Window::GetWindowSize()
{
    int width;
    int height;
    glfwGetWindowSize(m_GLFWwindow, &width, &height);
    m_windowSize = {(uint16_t)width, (uint16_t)height};
    return m_windowSize;
}

void Window::SetFullscreen(bool fullscreen)
{
    //TODO
}

// void Window::SetCustomCursor(GLFWimage* cursor_image)
// {
//     if (m_cursor != nullptr) glfwDestroyCursor(m_cursor);
//     m_cursor = glfwCreateCursor(cursor_image, 0, 0);
//     glfwSetCursor(m_GLFWwindow, m_cursor);
// }

// void Window::SetStandardCursor(int32_t shape)
// {
//     //GLFW_ARROW_CURSOR     == 0x00036001
//     //GLFW_IBEAM_CURSOR     == 0x00036002
//     //GLFW_CROSSHAIR_CURSOR == 0x00036003
//     //GLFW_HAND_CURSOR      == 0x00036004
//     //GLFW_HRESIZE_CURSOR   == 0x00036005
//     //GLFW_VRESIZE_CURSOR   == 0x00036006
//     if (m_cursor != nullptr) glfwDestroyCursor(m_cursor);
//     m_cursor = glfwCreateStandardCursor(shape);
//     glfwSetCursor(m_GLFWwindow, m_cursor);
// }

GLFWwindow* Window::GetWindowPtr()
{
    return m_GLFWwindow;
}