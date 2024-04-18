#include "EntityTable.hpp"



EntityTable::EntityTable() :
m_Entities(Vector<Entity>(CEIL4KB(ENTITY_IN_TABLE_LIMIT * BLENGTH(Entity)))),
m_EntityContainers(Buffer<EntityContainer, ENTITY_FRAGMENT_LIMIT>()),
m_AttachLookup(Buffer<uint16_t, ENTITY_FRAGMENT_LIMIT>()),
m_DetachLookup(Buffer<uint16_t, ENTITY_FRAGMENT_LIMIT>())
{
	for (size_t i = 0; i < m_AttachLookup.Length(); ++i)
		m_AttachLookup[i] = 0b1111111111111111;
	for (size_t i = 0; i < m_DetachLookup.Length(); ++i)
		m_DetachLookup[i] = 0b1111111111111111;

}
EntityTable::~EntityTable()
{
}



void EntityTable::CreateContainer(size_t element_length, uint16_t fragment_id, bool is_data)
{
	new(&m_EntityContainers[fragment_id]) EntityContainer(element_length, is_data);

}
