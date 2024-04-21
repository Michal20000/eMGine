#pragma once
#include <cstdint>
#include "Errors.hpp"
#include "Memory.hpp"



template<class ELEMENT_CLASS>
class Vector
{
	public:
	// TODO: Delete;
	// static_assert(sizeof(ELEMENT_CLASS) <= 4096, "Element Length should not be greater than 4096B");
	Vector(size_t reserve_length = 256 * 1024 * 1024);
	Vector(const Vector<ELEMENT_CLASS>& ob);
	Vector(Vector<ELEMENT_CLASS>&& ob);
	~Vector();

	Vector<ELEMENT_CLASS>& operator=(const Vector<ELEMENT_CLASS>& ob);
	Vector<ELEMENT_CLASS>& operator=(Vector<ELEMENT_CLASS>&& ob);
	bool operator==(const Vector<ELEMENT_CLASS>& ob);
	bool operator!=(const Vector<ELEMENT_CLASS>& ob);

	size_t Length();
	size_t BLength();

	ELEMENT_CLASS* Begin();
	const ELEMENT_CLASS* Begin() const;
	ELEMENT_CLASS* End();
	const ELEMENT_CLASS* End() const;

	ELEMENT_CLASS& At(size_t index);
	const ELEMENT_CLASS& At(size_t index) const;
	ELEMENT_CLASS& operator[](size_t index);
	const ELEMENT_CLASS& operator[](size_t index) const;
	void Clear();

	template<class... ARGUMENTS>
	ELEMENT_CLASS& EmplaceBack(ARGUMENTS&&... arguments);
	void PushBack(const ELEMENT_CLASS& ob);
	void PushBack(ELEMENT_CLASS&& ob);
	void RemoveBack();

	template<class... ARGUMENTS>
	ELEMENT_CLASS& Emplace(size_t index, ARGUMENTS&&... arguments);
	void Push(size_t index, const ELEMENT_CLASS& ob);
	void Push(size_t index, ELEMENT_CLASS&& ob);
	void Remove(size_t index);

	private:
	ELEMENT_CLASS* m_BeginPointer;
	ELEMENT_CLASS* m_EndPointer;
	uint8_t* m_AllocatePointer;
	uint8_t* m_ReservePointer;

	void Free();
	void Grow();
	void Shrink();

};



template<class ELEMENT_CLASS>
Vector<ELEMENT_CLASS>::Vector(size_t reserve_length)
{
	DEBUG_THROW(reserve_length == 0, std::logic_error, "Reserve Length should not be Zero");
	DEBUG_THROW((reserve_length & 4095) != 0, std::logic_error, "Reserve Length should be divisible by 4096");
	m_BeginPointer = (ELEMENT_CLASS*)VReserve(reserve_length);
	m_EndPointer = (ELEMENT_CLASS*)m_BeginPointer;
	m_AllocatePointer = (uint8_t*)m_BeginPointer;
	m_ReservePointer = (uint8_t*)m_BeginPointer; m_ReservePointer += reserve_length;

}
template<class ELEMENT_CLASS>
Vector<ELEMENT_CLASS>::Vector(const Vector<ELEMENT_CLASS>& ob)
{
	DEBUG_THROW(ob.m_BeginPointer == nullptr, std::runtime_error, "There is no data to be copied from Source Vector");
	size_t size = (uint8_t*)ob.m_EndPointer - (uint8_t*)ob.m_BeginPointer;
	size_t allocate_size = (uint8_t*)ob.m_AllocatePointer - (uint8_t*)ob.m_BeginPointer;
	size_t reserve_size = (uint8_t*)ob.m_ReservePointer - (uint8_t*)ob.m_BeginPointer;
	m_BeginPointer = (ELEMENT_CLASS*)VReserve(reserve_size);
	m_EndPointer = (ELEMENT_CLASS*)((uint8_t*)m_BeginPointer + size);
	m_AllocatePointer = (uint8_t*)m_BeginPointer + allocate_size;
	m_ReservePointer = (uint8_t*)m_BeginPointer + reserve_size;
	VAllocate(m_BeginPointer, allocate_size);

	ELEMENT_CLASS* data = Begin();
	for (const ELEMENT_CLASS* it = ob.Begin(); it < ob.End(); ++it) {
		const ELEMENT_CLASS& ob = *it;
		new(data) ELEMENT_CLASS(ob);
		data += 1;
	
	}

}
template<class ELEMENT_CLASS>
Vector<ELEMENT_CLASS>::Vector(Vector<ELEMENT_CLASS>&& ob)
{
	m_BeginPointer = ob.m_BeginPointer;
	m_EndPointer = ob.m_EndPointer;
	m_AllocatePointer = ob.m_AllocatePointer;
	m_ReservePointer = ob.m_ReservePointer;
	ob.m_BeginPointer = nullptr;
	ob.m_EndPointer = nullptr;
	ob.m_AllocatePointer = nullptr;
	ob.m_ReservePointer = nullptr;

}
template<class ELEMENT_CLASS>
Vector<ELEMENT_CLASS>::~Vector()
{
	Free();

}

template<class ELEMENT_CLASS>
Vector<ELEMENT_CLASS>& Vector<ELEMENT_CLASS>::operator=(const Vector<ELEMENT_CLASS>& ob)
{
	DEBUG_THROW(ob.m_BeginPointer == nullptr, std::runtime_error, "There is no data to be copied from Source Vector");
	Free();
	size_t size = (uint8_t*)ob.m_EndPointer - (uint8_t*)ob.m_BeginPointer;
	size_t allocate_size = (uint8_t*)ob.m_AllocatePointer - (uint8_t*)ob.m_BeginPointer;
	size_t reserve_size = (uint8_t*)ob.m_ReservePointer - (uint8_t*)ob.m_BeginPointer;
	m_BeginPointer = (ELEMENT_CLASS*)VReserve(reserve_size);
	m_EndPointer = (ELEMENT_CLASS*)((uint8_t*)m_BeginPointer + size);
	m_AllocatePointer = (uint8_t*)m_BeginPointer + allocate_size;
	m_ReservePointer = (uint8_t*)m_BeginPointer + reserve_size;
	VAllocate(m_BeginPointer, allocate_size);

	ELEMENT_CLASS* data = Begin();
	for (const ELEMENT_CLASS* it = ob.Begin(); it < ob.End(); ++it) {
		const ELEMENT_CLASS& ob = *it;
		new(data) ELEMENT_CLASS(ob);
		data += 1;
	
	}
	return *this;

}
template<class ELEMENT_CLASS>
Vector<ELEMENT_CLASS>& Vector<ELEMENT_CLASS>::operator=(Vector<ELEMENT_CLASS>&& ob)
{
	Free();
	m_BeginPointer = ob.m_BeginPointer;
	m_EndPointer = ob.m_EndPointer;
	m_AllocatePointer = ob.m_AllocatePointer;
	m_ReservePointer = ob.m_ReservePointer;
	ob.m_BeginPointer = nullptr;
	ob.m_EndPointer = nullptr;
	ob.m_AllocatePointer = nullptr;
	ob.m_ReservePointer = nullptr;
	return *this;

}
template<class ELEMENT_CLASS>
bool Vector<ELEMENT_CLASS>::operator==(const Vector<ELEMENT_CLASS>& ob)
{
	static_assert(false, "TODO: Will be added in Future");

}
template<class ELEMENT_CLASS>
bool Vector<ELEMENT_CLASS>::operator!=(const Vector<ELEMENT_CLASS>& ob)
{
	static_assert(false, "TODO: Will be added in Future");

}

template<class ELEMENT_CLASS>
size_t Vector<ELEMENT_CLASS>::Length()
{
	size_t result = m_EndPointer - m_BeginPointer;
	return result;

}
template<class ELEMENT_CLASS>
size_t Vector<ELEMENT_CLASS>::BLength()
{
	size_t result = (uint8_t*)m_EndPointer - (uint8_t*)m_BeginPointer;
	return result;

}

template<class ELEMENT_CLASS>
ELEMENT_CLASS* Vector<ELEMENT_CLASS>::Begin()
{
	return m_BeginPointer;

}
template<class ELEMENT_CLASS>
const ELEMENT_CLASS* Vector<ELEMENT_CLASS>::Begin() const
{
	return m_BeginPointer;

}
template<class ELEMENT_CLASS>
ELEMENT_CLASS* Vector<ELEMENT_CLASS>::End()
{
	return m_EndPointer;

}
template<class ELEMENT_CLASS>
const ELEMENT_CLASS* Vector<ELEMENT_CLASS>::End() const
{
	return m_EndPointer;

}

template<class ELEMENT_CLASS>
ELEMENT_CLASS& Vector<ELEMENT_CLASS>::At(size_t index)
{
	ELEMENT_CLASS* ob_pointer = m_BeginPointer + index;
	THROW(ob_pointer >= m_EndPointer, std::out_of_range, "Index is out of Range");
	return *ob_pointer;

}
template<class ELEMENT_CLASS>
const ELEMENT_CLASS& Vector<ELEMENT_CLASS>::At(size_t index) const
{
	ELEMENT_CLASS* ob_pointer = m_BeginPointer + index;
	THROW(ob_pointer >= m_EndPointer, std::out_of_range, "Index is out of Range");
	return *ob_pointer;

}
template<class ELEMENT_CLASS>
ELEMENT_CLASS& Vector<ELEMENT_CLASS>::operator[](size_t index)
{
	ELEMENT_CLASS* ob_pointer = m_BeginPointer + index;
	DEBUG_THROW(ob_pointer >= m_EndPointer, std::out_of_range, "Index is out of Range");
	return *ob_pointer;

}
template<class ELEMENT_CLASS>
const ELEMENT_CLASS& Vector<ELEMENT_CLASS>::operator[](size_t index) const
{
	ELEMENT_CLASS* ob_pointer = m_BeginPointer + index;
	DEBUG_THROW(ob_pointer >= m_EndPointer, std::out_of_range, "Index is out of Range");
	return *ob_pointer;

}
template<class ELEMENT_CLASS>
void Vector<ELEMENT_CLASS>::Clear()
{
	size_t allocate_length = (uint8_t*)m_AllocatePointer - (uint8_t*)m_BeginPointer;
	if (allocate_length == 0) return;
	for (ELEMENT_CLASS* it = Begin(); it < End(); ++it)
		it->~ELEMENT_CLASS();

	VDeallocate((void*)m_BeginPointer, allocate_length);
	m_EndPointer = m_BeginPointer;
	m_AllocatePointer = (uint8_t*)m_BeginPointer;

}

template<class ELEMENT_CLASS>
template<class... ARGUMENTS>
ELEMENT_CLASS& Vector<ELEMENT_CLASS>::EmplaceBack(ARGUMENTS&&... arguments)
{
	Grow();
	ELEMENT_CLASS* ob_pointer = m_EndPointer - 1;
	new(ob_pointer) ELEMENT_CLASS(std::forward<ARGUMENTS>(arguments)...);
	return *ob_pointer;

}
template<class ELEMENT_CLASS>
void Vector<ELEMENT_CLASS>::PushBack(const ELEMENT_CLASS& ob)
{
	Grow();
	ELEMENT_CLASS* ob_pointer = m_EndPointer - 1;
	new(ob_pointer) ELEMENT_CLASS(ob);

}
template<class ELEMENT_CLASS>
void Vector<ELEMENT_CLASS>::PushBack(ELEMENT_CLASS&& ob)
{
	Grow();
	ELEMENT_CLASS* ob_pointer = m_EndPointer - 1;
	new(ob_pointer) ELEMENT_CLASS(std::move(ob));

}
template<class ELEMENT_CLASS>
void Vector<ELEMENT_CLASS>::RemoveBack()
{
	if (m_BeginPointer == m_EndPointer) return;
	ELEMENT_CLASS* ob_pointer = m_EndPointer - 1;
	ob_pointer->~ELEMENT_CLASS();
	Shrink();

}

template<class ELEMENT_CLASS>
template<class... ARGUMENTS>
ELEMENT_CLASS& Vector<ELEMENT_CLASS>::Emplace(size_t index, ARGUMENTS&&... arguments)
{
	ELEMENT_CLASS* ob_pointer = m_BeginPointer + index;
	if (ob_pointer >= m_EndPointer)
		return EmplaceBack(std::forward<ARGUMENTS>(arguments)...);
	
	Grow();
	memcpy(m_EndPointer - 1, ob_pointer, sizeof(ELEMENT_CLASS));
	new(ob_pointer) ELEMENT_CLASS(std::forward<ARGUMENTS>(arguments)...);
	return *ob_pointer;

}
template<class ELEMENT_CLASS>
void Vector<ELEMENT_CLASS>::Push(size_t index, const ELEMENT_CLASS& ob)
{
	ELEMENT_CLASS* ob_pointer = m_BeginPointer + index;
	if (ob_pointer >= m_EndPointer) {
		PushBack(ob);
		return;

	}

	Grow();
	memcpy(m_EndPointer - 1, ob_pointer, sizeof(ELEMENT_CLASS));
	new(ob_pointer) ELEMENT_CLASS(ob);

}
template<class ELEMENT_CLASS>
void Vector<ELEMENT_CLASS>::Push(size_t index, ELEMENT_CLASS&& ob)
{
	ELEMENT_CLASS* ob_pointer = m_BeginPointer + index;
	if (ob_pointer >= m_EndPointer) {
		PushBack(std::move(ob));
		return;

	}

	Grow();
	memcpy(m_EndPointer - 1, ob_pointer, sizeof(ELEMENT_CLASS));
	new(ob_pointer) ELEMENT_CLASS(std::move(ob));

}
template<class ELEMENT_CLASS>
void Vector<ELEMENT_CLASS>::Remove(size_t index)
{
	ELEMENT_CLASS* ob_pointer = m_BeginPointer + index;
	if (ob_pointer >= m_EndPointer) return;
	ob_pointer->~ELEMENT_CLASS();
	memcpy(ob_pointer, m_EndPointer - 1, sizeof(ELEMENT_CLASS));
	Shrink();

}

template<class ELEMENT_CLASS>
void Vector<ELEMENT_CLASS>::Free()
{
	size_t reserve_length = (uint8_t*)m_ReservePointer - (uint8_t*)m_BeginPointer;
	if (reserve_length == 0) return;
	for (ELEMENT_CLASS* it = Begin(); it < End(); ++it)
		it->~ELEMENT_CLASS();
	
	VFree(m_BeginPointer, reserve_length);
	m_BeginPointer = nullptr;
	m_EndPointer = nullptr;
	m_AllocatePointer = nullptr;
	m_ReservePointer = nullptr;

}
template<class ELEMENT_CLASS>
void Vector<ELEMENT_CLASS>::Grow()
{
	ELEMENT_CLASS* ob_end = m_EndPointer + 1;
	m_EndPointer = ob_end;
	while ((void*)ob_end > (void*)m_AllocatePointer) {
		THROW(m_AllocatePointer + 4096 > m_ReservePointer, std::runtime_error, "Vector Buffer is already Full");
		VAllocate(m_AllocatePointer, 4096);
		m_AllocatePointer = m_AllocatePointer + 4096;

	}

}
template<class ELEMENT_CLASS>
void Vector<ELEMENT_CLASS>::Shrink()
{
	ELEMENT_CLASS* ob_end = m_EndPointer - 1;
	m_EndPointer = ob_end;
	while ((void*)ob_end <= (void*)(m_AllocatePointer - 4096)) {
		VDeallocate((m_AllocatePointer - 4096), 4096);
		m_AllocatePointer = (m_AllocatePointer - 4096);

	}

}
