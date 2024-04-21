#pragma once
#include <cstdint>
#include "Errors.hpp"



template<size_t LENGTH>
struct BitField
{
	public:
	static_assert((LENGTH & 7) == 0, "Length should be divisible by Eight");
	BitField() = default;
	BitField(const BitField<LENGTH>& ob) = default;
	BitField(BitField<LENGTH>&& ob) = default;
	~BitField() = default;

	BitField<LENGTH>& operator=(const BitField<LENGTH>& ob) = default;
	BitField<LENGTH>& operator=(BitField<LENGTH>&& ob) = default;
	bool operator==(const BitField<LENGTH>& ob) const = default;
	bool operator!=(const BitField<LENGTH>& ob) const = default;
	
	constexpr size_t Length() const;
	constexpr size_t BLength() const;

	void Fill64(uint64_t value);
	void Fill32(uint32_t value);
	void Fill16(uint16_t value);
	void Fill(uint8_t value);

	uint64_t& Ui64(size_t index);
	uint32_t& Ui32(size_t index);
	uint16_t& Ui16(size_t index);
	uint8_t& Ui(size_t index);
	const uint64_t& Ui64(size_t index) const;
	const uint32_t& Ui32(size_t index) const;
	const uint16_t& Ui16(size_t index) const;
	const uint8_t& Ui(size_t index) const;

	void True(size_t bit_index);
	void False(size_t bit_index);
	void Flip(size_t bit_index);
	bool At(size_t bit_index) const;
	bool operator[](size_t bit_index) const;
	
	BitField<LENGTH> operator&(const BitField<LENGTH>& ob) const;
	BitField<LENGTH> operator|(const BitField<LENGTH>& ob) const;
	BitField<LENGTH> operator^(const BitField<LENGTH>& ob) const;
	BitField<LENGTH> operator~() const;
	BitField<LENGTH> operator>>(size_t shift_value) const;
	BitField<LENGTH> operator<<(size_t shift_value) const;

	BitField<LENGTH>& operator&=(const BitField<LENGTH>& ob);
	BitField<LENGTH>& operator|=(const BitField<LENGTH>& ob);
	BitField<LENGTH>& operator^=(const BitField<LENGTH>& ob);
	BitField<LENGTH>& operator>>=(size_t shift_value);
	BitField<LENGTH>& operator<<=(size_t shift_value);
	const BitField<LENGTH>& operator&=(const BitField<LENGTH>& ob) const;
	const BitField<LENGTH>& operator|=(const BitField<LENGTH>& ob) const;
	const BitField<LENGTH>& operator^=(const BitField<LENGTH>& ob) const;
	const BitField<LENGTH>& operator>>=(size_t shift_value) const;
	const BitField<LENGTH>& operator<<=(size_t shift_value) const;

	private:
	uint8_t m_Buffer[LENGTH >> 3];

};



template<size_t LENGTH>
constexpr size_t BitField<LENGTH>::Length() const
{
	return LENGTH & ~7UL;

}
template<size_t LENGTH>
constexpr size_t BitField<LENGTH>::BLength() const
{
	return LENGTH >> 3;

}

template<size_t LENGTH>
void BitField<LENGTH>::Fill64(uint64_t value)
{
	static_assert((sizeof(*this) & 7) == 0, "BLength should be divisible by Eight");
	uint64_t* begin = (uint64_t*)&m_Buffer[0];
	uint64_t* end = (uint64_t*)&m_Buffer[BLength()];
	for (uint64_t* it = begin; it < end; ++it)
		*it = value;

}
template<size_t LENGTH>
void BitField<LENGTH>::Fill32(uint32_t value)
{
	static_assert((sizeof(*this) & 3) == 0, "BLength should be divisible by Four");
	uint32_t* begin = (uint32_t*)&m_Buffer[0];
	uint32_t* end = (uint32_t*)&m_Buffer[BLength()];
	for (uint32_t* it = begin; it < end; ++it)
		*it = value;

}
template<size_t LENGTH>
void BitField<LENGTH>::Fill16(uint16_t value)
{
	static_assert((sizeof(*this) & 1) == 0, "BLength should be divisible by Two");
	uint16_t* begin = (uint16_t*)&m_Buffer[0];
	uint16_t* end = (uint16_t*)&m_Buffer[BLength()];
	for (uint16_t* it = begin; it < end; ++it)
		*it = value;

}
template<size_t LENGTH>
void BitField<LENGTH>::Fill(uint8_t value)
{
	uint8_t* begin = (uint8_t*)&m_Buffer[0];
	uint8_t* end = (uint8_t*)&m_Buffer[BLength()];
	for (uint8_t* it = begin; it < end; ++it)
		*it = value;

}

template<size_t LENGTH>
uint64_t& BitField<LENGTH>::Ui64(size_t index)
{
	static_assert((sizeof(*this) & 7) == 0, "BLength should be divisible by Eight");
	DEBUG_THROW(index >= (BLength() >> 3), std::out_of_range, "Index is out of Range");
	return ((uint64_t*)&m_Buffer[0])[index];

}
template<size_t LENGTH>
uint32_t& BitField<LENGTH>::Ui32(size_t index)
{
	static_assert((sizeof(*this) & 3) == 0, "BLength should be divisible by Four");
	DEBUG_THROW(index >= (BLength() >> 2), std::out_of_range, "Index is out of Range");
	return ((uint32_t*)&m_Buffer[0])[index];

}
template<size_t LENGTH>
uint16_t& BitField<LENGTH>::Ui16(size_t index)
{
	static_assert((sizeof(*this) & 1) == 0, "BLength should be divisible by Two");
	DEBUG_THROW(index >= (BLength() >> 1), std::out_of_range, "Index is out of Range");
	return ((uint16_t*)&m_Buffer[0])[index];

}
template<size_t LENGTH>
uint8_t& BitField<LENGTH>::Ui(size_t index)
{
	DEBUG_THROW(index >= BLength(), std::out_of_range, "Index is out of Range");
	return m_Buffer[index];

}
template<size_t LENGTH>
const uint64_t& BitField<LENGTH>::Ui64(size_t index) const
{
	static_assert((sizeof(*this) & 7) == 0, "BLength should be divisible by Eight");
	DEBUG_THROW(index >= (BLength() >> 3), std::out_of_range, "Index is out of Range");
	return ((uint64_t*)&m_Buffer[0])[index];

}
template<size_t LENGTH>
const uint32_t& BitField<LENGTH>::Ui32(size_t index) const
{
	static_assert((sizeof(*this) & 3) == 0, "BLength should be divisible by Four");
	DEBUG_THROW(index >= (BLength() >> 2), std::out_of_range, "Index is out of Range");
	return ((uint32_t*)&m_Buffer[0])[index];

}
template<size_t LENGTH>
const uint16_t& BitField<LENGTH>::Ui16(size_t index) const
{
	static_assert((sizeof(*this) & 1) == 0, "BLength should be divisible by Two");
	DEBUG_THROW(index >= (BLength() >> 1), std::out_of_range, "Index is out of Range");
	return ((uint16_t*)&m_Buffer[0])[index];

}
template<size_t LENGTH>
const uint8_t& BitField<LENGTH>::Ui(size_t index) const
{
	DEBUG_THROW(index >= BLength(), std::out_of_range, "Index is out of Range");
	return m_Buffer[index];

}

template<size_t LENGTH>
void BitField<LENGTH>::True(size_t bit_index)
{
	size_t index = bit_index >> 3;
	size_t bit = bit_index & 7;
	DEBUG_THROW(bit_index >= Length(), std::out_of_range, "Bit Index is out of Range");
	m_Buffer[index] |= (1 << bit);

}
template<size_t LENGTH>
void BitField<LENGTH>::False(size_t bit_index)
{
	size_t index = bit_index >> 3;
	size_t bit = bit_index & 7;
	DEBUG_THROW(bit_index >= Length(), std::out_of_range, "Bit Index is out of Range");
	m_Buffer[index] &= ~(1 << bit);

}
template<size_t LENGTH>
void BitField<LENGTH>::Flip(size_t bit_index)
{
	size_t index = bit_index >> 3;
	size_t bit = bit_index & 7;
	DEBUG_THROW(bit_index >= Length(), std::out_of_range, "Bit Index is out of Range");
	m_Buffer[index] ^= (1 << bit);

}
template<size_t LENGTH>

bool BitField<LENGTH>::At(size_t bit_index) const
{
	size_t index = bit_index >> 3;
	size_t bit = bit_index & 7;
	THROW(bit_index >= Length(), std::out_of_range, "Bit Index is out of Range");
	return m_Buffer[index] & (1 << bit);

}
template<size_t LENGTH>
bool BitField<LENGTH>::operator[](size_t bit_index) const
{
	size_t index = bit_index >> 3;
	size_t bit = bit_index & 7;
	DEBUG_THROW(bit_index >= Length(), std::out_of_range, "Bit Index is out of Range");
	return m_Buffer[index] & (1 << bit);

}

template<size_t LENGTH>
BitField<LENGTH> BitField<LENGTH>::operator&(const BitField<LENGTH>& ob) const
{
	BitField<LENGTH> result = BitField<LENGTH>();
	for (size_t i = 0; i < BLength(); ++i)
		result.m_Buffer[i] = m_Buffer[i] & ob.m_Buffer[i];
	return result;

}
template<size_t LENGTH>
BitField<LENGTH> BitField<LENGTH>::operator|(const BitField<LENGTH>& ob) const
{
	BitField<LENGTH> result = BitField<LENGTH>();
	for (size_t i = 0; i < BLength(); ++i)
		result.m_Buffer[i] = m_Buffer[i] | ob.m_Buffer[i];
	return result;

}
template<size_t LENGTH>
BitField<LENGTH> BitField<LENGTH>::operator^(const BitField<LENGTH>& ob) const
{
	BitField<LENGTH> result = BitField<LENGTH>();
	for (size_t i = 0; i < BLength(); ++i)
		result.m_Buffer[i] = m_Buffer[i] ^ ob.m_Buffer[i];
	return result;

}
template<size_t LENGTH>
BitField<LENGTH> BitField<LENGTH>::operator~() const
{
	BitField<LENGTH> result = BitField<LENGTH>();
	for (size_t i = 0; i < BLength(); ++i)
		result.m_Buffer[i] = ~m_Buffer[i];
	return result;

}
template<size_t LENGTH>
BitField<LENGTH> BitField<LENGTH>::operator>>(size_t shift_value) const
{
	static_assert(false, "TODO: Will be added in Future");

}
template<size_t LENGTH>
BitField<LENGTH> BitField<LENGTH>::operator<<(size_t shift_value) const
{
	static_assert(false, "TODO: Will be added in Future");

}

template<size_t LENGTH>
BitField<LENGTH>& BitField<LENGTH>::operator&=(const BitField<LENGTH>& ob)
{
	for (size_t i = 0; i < BLength(); ++i)
		m_Buffer[i] &= ob.m_Buffer[i];
	return *this;

}
template<size_t LENGTH>
BitField<LENGTH>& BitField<LENGTH>::operator|=(const BitField<LENGTH>& ob)
{
	for (size_t i = 0; i < BLength(); ++i)
		m_Buffer[i] |= ob.m_Buffer[i];
	return *this;

}
template<size_t LENGTH>
BitField<LENGTH>& BitField<LENGTH>::operator^=(const BitField<LENGTH>& ob)
{
	for (size_t i = 0; i < BLength(); ++i)
		m_Buffer[i] ^= ob.m_Buffer[i];
	return *this;

}
template<size_t LENGTH>
BitField<LENGTH>& BitField<LENGTH>::operator>>=(size_t shift_value)
{
	static_assert(false, "TODO: Will be added in Future");

}
template<size_t LENGTH>
BitField<LENGTH>& BitField<LENGTH>::operator<<=(size_t shift_value)
{
	static_assert(false, "TODO: Will be added in Future");

}
template<size_t LENGTH>
const BitField<LENGTH>& BitField<LENGTH>::operator&=(const BitField<LENGTH>& ob) const
{
	for (size_t i = 0; i < BLength(); ++i)
		m_Buffer[i] &= ob.m_Buffer[i];
	return *this;

}
template<size_t LENGTH>
const BitField<LENGTH>& BitField<LENGTH>::operator|=(const BitField<LENGTH>& ob) const
{
	for (size_t i = 0; i < BLength(); ++i)
		m_Buffer[i] |= ob.m_Buffer[i];
	return *this;

}
template<size_t LENGTH>
const BitField<LENGTH>& BitField<LENGTH>::operator^=(const BitField<LENGTH>& ob) const
{
	for (size_t i = 0; i < BLength(); ++i)
		m_Buffer[i] ^= ob.m_Buffer[i];
	return *this;

}
template<size_t LENGTH>
const BitField<LENGTH>& BitField<LENGTH>::operator>>=(size_t shift_value) const
{
	static_assert(false, "TODO: Will be added in Future");

}
template<size_t LENGTH>
const BitField<LENGTH>& BitField<LENGTH>::operator<<=(size_t shift_value) const
{
	static_assert(false, "TODO: Will be added in Future");

}
