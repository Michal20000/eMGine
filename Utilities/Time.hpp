#pragma once
#include <cstdint>



class GLFWwindow;
class Time
{
	public:
	friend class Application;
	friend class Keyboard;
	friend class Mouse;
	friend void KeyFunction(GLFWwindow* window, int32_t key, int32_t code, int32_t action, int32_t mode);
	friend void CharacterFunction(GLFWwindow* window, uint32_t character);
	friend void MouseLocationFunction(GLFWwindow* window, double location_x, double location_y);
	friend void MouseButtonFunction(GLFWwindow* window, int32_t button, int32_t action, int32_t modifier_bits);
	friend void MouseEnterFunction(GLFWwindow* window, int32_t is_entered);
	friend void MouseScrollFunction(GLFWwindow* window, double offset_x, double offset_y);

	Time() = delete;
	Time(const Time& ob) = delete;
	Time(Time&& ob) = delete;
	~Time() = delete;
	Time& operator=(const Time& ob) = delete;
	Time& operator=(Time&& ob) = delete;
	
	static int64_t Now();
	static float Duration(int64_t before, int64_t after);
	// TODO: this with this...
	static float FrameTime();
	static float PeriodicTime();

	private:
	static int64_t s_Before;
	static float s_DeltaTime;

};
