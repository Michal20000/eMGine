#include "Keyboard.hpp"
#include "Time.hpp"
#include "Errors.hpp"



int64_t Keyboard::s_Keys[s_Length];
int64_t Keyboard::s_CharacterTime = 0;
char Keyboard::s_Character = 0;



bool Keyboard::IsPressed(uint16_t key)
{
	uint16_t key_index = key - s_Offset;
	DEBUG_THROW(key_index >= s_Length, std::runtime_error, "Key is not valid");
	return s_Keys[key_index] < 0;

}
bool Keyboard::IsReleased(uint16_t key)
{
	uint16_t key_index = key - s_Offset;
	DEBUG_THROW(key_index >= s_Length, std::runtime_error, "Key is not valid");
	return s_Keys[key_index] >= 0;

}
float Keyboard::Duration(uint16_t key)
{
	uint16_t key_index = key - s_Offset;
	DEBUG_THROW(key_index >= s_Length, std::runtime_error, "Key is not valid");
	int64_t action_time = s_Keys[key_index] >= 0 ? s_Keys[key_index] : -s_Keys[key_index];
	float duration = Time::Duration(action_time, Time::s_Before);
	return duration;

}



bool Keyboard::IsCharacter()
{
	return Keyboard::s_CharacterTime == Time::s_Before;

}
char Keyboard::Character()
{
	DEBUG_THROW(Keyboard::s_CharacterTime != Time::s_Before, std::runtime_error, "There is no character in queue");
	return s_Character;

}
