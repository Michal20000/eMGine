#pragma once
#include "Vector2F.hpp"
#include <cstdint>



#define LEFT_MOUSE_BUTTON 0
#define RIGHT_MOUSE_BUTTON 1
#define MIDDLE_MOUSE_BUTTON 2



class GLFWwindow;
class Mouse
{
	public:
	friend void MouseLocationFunction(GLFWwindow* window, double location_x, double location_y);
	friend void MouseButtonFunction(GLFWwindow* window, int32_t button, int32_t action, int32_t modifier_bits);
	friend void MouseEnterFunction(GLFWwindow* window, int32_t is_entered);
	friend void MouseScrollFunction(GLFWwindow* window, double offset_x, double offset_y);

	static bool IsPressed(uint16_t button);
	static bool IsReleased(uint16_t button);
	static float Duration(uint16_t button);

	static bool HasEntered();
	static bool HasLeft();
	static bool IsEntered();
	static bool IsLeft();

	static Vector2F Location();
	static Vector2F Motion();
	static Vector2F ScrollMotion();

	private:
	static constexpr size_t s_Length = 8;
	static int64_t s_Buttons[s_Length];
	static int64_t s_Entered;
	static int64_t s_MotionTime;
	static int64_t s_ScrollMotionTime;
	static Vector2F s_Location;
	static Vector2F s_Motion;
	static Vector2F s_ScrollMotion;

};
