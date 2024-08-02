#include "Mouse.hpp"
#include "Time.hpp"
#include "Errors.hpp"



int64_t Mouse::s_Buttons[s_Length];
int64_t Mouse::s_Entered = 0;
int64_t Mouse::s_MotionTime = 0;
int64_t Mouse::s_ScrollMotionTime = 0;
Vector2F Mouse::s_Location;
Vector2F Mouse::s_Motion;
Vector2F Mouse::s_ScrollMotion;



bool Mouse::IsPressed(uint16_t button)
{
	DEBUG_THROW(button >= s_Length, std::runtime_error, "Button is not valid");
	return s_Buttons[button] < 0;

}
bool Mouse::IsReleased(uint16_t button)
{
	DEBUG_THROW(button >= s_Length, std::runtime_error, "Button is not valid");
	return s_Buttons[button] >= 0;

}
float Mouse::Duration(uint16_t button)
{
	DEBUG_THROW(button >= s_Length, std::runtime_error, "Button is not valid");
	int64_t action_time = s_Buttons[button] >= 0 ? s_Buttons[button] : -s_Buttons[button];
	float duration = Time::Duration(action_time, Time::s_Before);
	return duration;

}

bool Mouse::HasEntered()
{
	int64_t action_time = s_Entered >= 0 ? s_Entered : -s_Entered;
	return s_Entered >= 0 && action_time == Time::s_Before;

}
bool Mouse::HasLeft()
{
	int64_t action_time = s_Entered >= 0 ? s_Entered : -s_Entered;
	return s_Entered < 0 && action_time == Time::s_Before;

}
bool Mouse::IsEntered()
{
	int64_t action_time = s_Entered >= 0 ? s_Entered : -s_Entered;
	return s_Entered >= 0 && action_time < Time::s_Before;

}
bool Mouse::IsLeft()
{
	int64_t action_time = s_Entered >= 0 ? s_Entered : -s_Entered;
	return s_Entered < 0 && action_time < Time::s_Before;

}

Vector2F Mouse::Location()
{
	return s_Location;

}
Vector2F Mouse::Motion()
{
	if (s_MotionTime == Time::s_Before)
		return s_Motion;
	
	Vector2F result;
	result.X = 0.0F;
	result.Y = 0.0F;
	return result;

}
Vector2F Mouse::ScrollMotion()
{
	if (s_ScrollMotionTime == Time::s_Before)
		return s_ScrollMotion;

	Vector2F result;
	result.X = 0.0F;
	result.Y = 0.0F;
	return result;

}
