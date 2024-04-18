#pragma once
#include "EntityUtilities.hpp"



class EntityView
{
	public:
	friend class EntityEngine;
	EntityView(const EntityView& ob) = default;
	EntityView(EntityView&& ob) = default;
	~EntityView() = default;
	EntityView& operator=(const EntityView& ob) = delete;
	EntityView& operator=(EntityView&& ob) = delete;

	bool Verify();
	void operator++();
	void operator++(int32_t);
	Entity Record();
	template<class CLASS>
	CLASS& Fragment();

	private:
	EntityEngine& m_EntityEngine;
	uint16_t* m_TableCurrent;
	uint16_t* m_TableEnd;
	uint32_t m_RecordCurrent;
	uint32_t m_RecordEnd;
	EntityView(EntityEngine& entity_engine, uint16_t* table_begin, uint16_t* table_end);

};
