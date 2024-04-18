#pragma once
#include "Errors.hpp"



template<class ELEMENT_CLASS, size_t LENGTH>
class Buffer
{
	public:
	Buffer() = default;
	Buffer(const Buffer<ELEMENT_CLASS, LENGTH>& ob) = default;
	Buffer(Buffer<ELEMENT_CLASS, LENGTH>&& ob) = default;
	~Buffer() = default;

	Buffer<ELEMENT_CLASS, LENGTH>& operator=(const Buffer<ELEMENT_CLASS, LENGTH>& ob) = default;
	Buffer<ELEMENT_CLASS, LENGTH>& operator=(Buffer<ELEMENT_CLASS, LENGTH>&& ob) = default;
	bool operator==(const Buffer<ELEMENT_CLASS, LENGTH>& ob) const = default;
	bool operator!=(const Buffer<ELEMENT_CLASS, LENGTH>& ob) const = default;

	constexpr size_t Length() const;
	constexpr size_t BLength() const;

	ELEMENT_CLASS* Begin();
	const ELEMENT_CLASS* Begin() const;
	ELEMENT_CLASS* End();
	const ELEMENT_CLASS* End() const;

	ELEMENT_CLASS& At(size_t index);
	const ELEMENT_CLASS& At(size_t index) const;
	ELEMENT_CLASS& operator[](size_t index);
	const ELEMENT_CLASS& operator[](size_t index) const;

	private:
	ELEMENT_CLASS m_Buffer[LENGTH];

};



template<class ELEMENT_CLASS, size_t LENGTH>
constexpr size_t Buffer<ELEMENT_CLASS, LENGTH>::Length() const
{
	return LENGTH;

}
template<class ELEMENT_CLASS, size_t LENGTH>
constexpr size_t Buffer<ELEMENT_CLASS, LENGTH>::BLength() const
{
	return LENGTH * sizeof(ELEMENT_CLASS);

}

template<class ELEMENT_CLASS, size_t LENGTH>
ELEMENT_CLASS* Buffer<ELEMENT_CLASS, LENGTH>::Begin()
{
	return m_Buffer[0];

}
template<class ELEMENT_CLASS, size_t LENGTH>
const ELEMENT_CLASS* Buffer<ELEMENT_CLASS, LENGTH>::Begin() const
{
	return m_Buffer[0];

}
template<class ELEMENT_CLASS, size_t LENGTH>
ELEMENT_CLASS* Buffer<ELEMENT_CLASS, LENGTH>::End()
{
	return m_Buffer[LENGTH - 1];

}
template<class ELEMENT_CLASS, size_t LENGTH>
const ELEMENT_CLASS* Buffer<ELEMENT_CLASS, LENGTH>::End() const
{
	return m_Buffer[LENGTH - 1];

}

template<class ELEMENT_CLASS, size_t LENGTH>
ELEMENT_CLASS& Buffer<ELEMENT_CLASS, LENGTH>::At(size_t index)
{
	THROW(index >= Length(), std::out_of_range, "Index is out of Range");
	return m_Buffer[index];

}
template<class ELEMENT_CLASS, size_t LENGTH>
const ELEMENT_CLASS& Buffer<ELEMENT_CLASS, LENGTH>::At(size_t index) const
{
	THROW(index >= Length(), std::out_of_range, "Index is out of Range");
	return m_Buffer[index];

}
template<class ELEMENT_CLASS, size_t LENGTH>
ELEMENT_CLASS& Buffer<ELEMENT_CLASS, LENGTH>::operator[](size_t index)
{
	DEBUG_THROW(index >= Length(), std::out_of_range, "Index is out of Range");
	return m_Buffer[index];

}
template<class ELEMENT_CLASS, size_t LENGTH>
const ELEMENT_CLASS& Buffer<ELEMENT_CLASS, LENGTH>::operator[](size_t index) const
{
	DEBUG_THROW(index >= Length(), std::out_of_range, "Index is out of Range");
	return m_Buffer[index];

}
