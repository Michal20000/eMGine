#pragma once
#include "EntityUtilities.hpp"
#include "EntityContainer.hpp"



class EntityTable
{
	public:
	friend class EntityEngine;
	EntityTable();
	EntityTable(const EntityTable& ob) = delete;
	EntityTable(EntityTable&& ob) = delete;
	~EntityTable();
	EntityTable& operator=(const EntityTable& ob) = delete;
	EntityTable& operator=(EntityTable&& ob) = delete;

	template<class CLASS>
	void CreateContainer();
	void CreateContainer(size_t element_length, uint16_t fragment_id, bool is_data);

	// private:
	Vector<Entity> m_Entities;
	Buffer<EntityContainer, ENTITY_FRAGMENT_LIMIT> m_EntityContainers; // 8KB
	Buffer<uint16_t, ENTITY_FRAGMENT_LIMIT> m_AttachLookup; // 512B
	Buffer<uint16_t, ENTITY_FRAGMENT_LIMIT> m_DetachLookup; // 512B

};



template<class CLASS>
void EntityTable::CreateContainer()
{
	new(&m_EntityContainers[CLASS::ID()]) EntityContainer(CLASS::BLength(), CLASS::IsData());

}
