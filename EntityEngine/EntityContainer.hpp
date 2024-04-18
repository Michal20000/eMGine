#pragma once
#include "EntityUtilities.hpp"



class EntityContainer
{
	public:
	friend class EntityEngine;
	EntityContainer(size_t element_length = 0, bool is_data = false);
	EntityContainer(const EntityContainer& ob) = delete;
	EntityContainer(EntityContainer&& ob) = delete;
	~EntityContainer();
	EntityContainer& operator=(const EntityContainer& ob) = delete;
	EntityContainer& operator=(EntityContainer&& ob) = delete;

	void Grow();
	void Shrink(uint32_t index);
	void* operator[](size_t index);
	void* At(size_t index);
	size_t Length();
	size_t BLength();

	private:
	uint8_t* m_BeginPointer;
	uint8_t* m_AllocatePointer;
	uint8_t* m_ReservePointer;
	uint32_t m_Length;
	uint32_t m_ElementLength;

};
