#pragma once
#include "./Dependencies/GLFW/include/glfw3.h"
#include <cstdint>

struct WindowSize
{
    uint16_t width;
    uint16_t height;
};

class Window
{
public:
    void Create(uint16_t window_size_x, uint16_t window_size_y, const char* title);
    void EnableCursor();
    void DisableCursor();
    void SetWindowSize(uint16_t width, uint16_t height);
    WindowSize GetWindowSize();
    void SetFullscreen(bool fullscreen);
    //void SetCustomCursor();
    //void SetStandardCursor();
    GLFWwindow* GetWindowPtr();
private:
    GLFWwindow* m_GLFWwindow;
    WindowSize m_windowSize;
    GLFWmonitor* m_primaryMonitor;
    GLFWwindow* m_share = nullptr;
    GLFWcursor* m_cursor;
};