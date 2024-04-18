#include "EntityContainer.hpp"



EntityContainer::EntityContainer(size_t element_length, bool is_data)
{
	THROW(element_length > 4096, std::length_error, "Element Length should not be greater than 4096B");
	size_t reserve_length = CEIL4KB(ENTITY_IN_TABLE_LIMIT * element_length);
	m_BeginPointer = is_data ? (uint8_t*)VReserve(reserve_length) : nullptr;
	m_AllocatePointer = is_data ? m_BeginPointer : nullptr;
	m_ReservePointer = is_data ? (m_BeginPointer + reserve_length) : nullptr;
	m_Length = 0;
	m_ElementLength = is_data ? element_length : 0;

}
EntityContainer::~EntityContainer()
{
	if (m_BeginPointer == nullptr) return;
	VFree(m_BeginPointer, m_ReservePointer - m_BeginPointer);

}

void EntityContainer::Grow()
{
	m_Length += 1;
	uint8_t* end_pointer = m_BeginPointer + m_Length * m_ElementLength;
	if (end_pointer > m_AllocatePointer) {
		uint8_t* allocate_pointer = m_AllocatePointer + 4096;
		THROW(allocate_pointer > m_ReservePointer, std::runtime_error, "Entity Container is already Full");
		VAllocate(m_AllocatePointer, 4096);
		m_AllocatePointer = allocate_pointer;

	}

}
void EntityContainer::Shrink(uint32_t index)
{
	if (index >= m_Length) return;
	m_Length -= 1;
	uint8_t* destination_pointer = m_BeginPointer + index * m_ElementLength;
	uint8_t* end_pointer = m_BeginPointer + m_Length * m_ElementLength;
	memcpy(destination_pointer, end_pointer, m_ElementLength);
	uint8_t* allocate_pointer = m_AllocatePointer - 4096;
	if (end_pointer <= allocate_pointer) {
		VDeallocate(allocate_pointer, 4096);
		m_AllocatePointer = allocate_pointer;

	}

}
void* EntityContainer::operator[](size_t index)
{
	DEBUG_THROW(index >= m_Length, std::out_of_range, "Index is out of Range");
	uint8_t* result = m_BeginPointer + index * m_ElementLength;
	return (void*)result;

}
void* EntityContainer::At(size_t index)
{
	THROW(index >= m_Length, std::out_of_range, "Index is out of Range");
	uint8_t* result = m_BeginPointer + index * m_ElementLength;
	return (void*)result;

}
size_t EntityContainer::Length()
{
	return m_Length;

}
size_t EntityContainer::BLength()
{
	return m_Length * m_ElementLength;

}
