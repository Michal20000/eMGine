#pragma once
#include "EntityUtilities.hpp"



template<class CLASS>
struct EntityFragment
{
	public:
	friend class EntityEngine;
	static size_t BLength();
	static uint16_t ID();
	static bool InRegister();
	static bool IsData();

	private:
	static size_t s_BLength;
	static uint16_t s_ID;
	static bool s_InRegister;
	static constexpr bool s_IsData = true;

};



template<class CLASS>
class EntityGroup : public EntityFragment<CLASS>
{
	public:
	friend class EntityEngine;
	static bool IsData();

	private:
	static constexpr bool s_IsData = false;

};



template<class CLASS>
size_t EntityFragment<CLASS>::s_BLength = 0;
template<class CLASS>
uint16_t EntityFragment<CLASS>::s_ID = 0;
template<class CLASS>
bool EntityFragment<CLASS>::s_InRegister = false;
template<class CLASS>
size_t EntityFragment<CLASS>::BLength()
{
	return s_BLength;

}
template<class CLASS>
uint16_t EntityFragment<CLASS>::ID()
{
	return s_ID;

}
template<class CLASS>
bool EntityFragment<CLASS>::InRegister()
{
	return s_InRegister;

}
template<class CLASS>
bool EntityFragment<CLASS>::IsData()
{
	return s_IsData;

}
template<class CLASS>
bool EntityGroup<CLASS>::IsData()
{
	return s_IsData;

}

