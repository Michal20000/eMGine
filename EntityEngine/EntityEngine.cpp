#include "EntityEngine.hpp"
#include <sstream>



Buffer<FrameFunction, ENTITY_FRAME_LIMIT> EntityEngine::s_FrameFunctions = Buffer<FrameFunction, ENTITY_FRAME_LIMIT>();
Buffer<FrameFunction, ENTITY_PERIODIC_LIMIT> EntityEngine::s_PeriodicFunctions = Buffer<FrameFunction, ENTITY_PERIODIC_LIMIT>();
size_t EntityEngine::s_FrameLength = 0;
size_t EntityEngine::s_PeriodicLength = 0;
size_t EntityEngine::FrameLength()
{
	return s_FrameLength;
	
}
size_t EntityEngine::PeriodicLength()
{
	return s_PeriodicLength;

}
uint16_t EntityEngine::GenerateFragmentID() {
	static constinit uint16_t entity_data_id = 0;
	THROW(entity_data_id == ENTITY_FRAGMENT_LIMIT, std::length_error, "Entity Data Length in Register can not be grater than " STRINGIFY(ENTITY_FRAGMENT_LIMIT));
	return entity_data_id++;

}

Buffer<CreateFunction, ENTITY_FRAGMENT_LIMIT> EntityEngine::s_CreateFunctions = Buffer<CreateFunction, ENTITY_FRAGMENT_LIMIT>();
Buffer<CreateFunction, ENTITY_FRAGMENT_LIMIT> EntityEngine::s_DestroyFunctions = Buffer<CreateFunction, ENTITY_FRAGMENT_LIMIT>();
Buffer<size_t, ENTITY_FRAGMENT_LIMIT> EntityEngine::s_FragmentBLengthBuffer = Buffer<size_t, ENTITY_FRAGMENT_LIMIT>();
Buffer<EntityBID, ENTITY_FRAGMENT_LIMIT> EntityEngine::s_FragmentBIDs = Buffer<EntityBID, ENTITY_FRAGMENT_LIMIT>();
size_t EntityEngine::s_FragmentsLength = 0;
BitField<ENTITY_FRAGMENT_LIMIT> EntityEngine::s_FragmentsIsData = BitField<ENTITY_FRAGMENT_LIMIT>();
size_t EntityEngine::FragmentsLength()
{
	return s_FragmentsLength;

}



EntityEngine::EntityEngine() :
m_Entities(Vector<EntityPointer>(CEIL4KB(ENTITY_LIMIT * BLENGTH(EntityPointer)))),
m_FreeEntityIDs(Vector<uint32_t>(CEIL4KB(ENTITY_LIMIT * BLENGTH(uint32_t)))),
m_Tables(Vector<EntityTable>(CEIL4KB(ENTITY_TABLE_LIMIT * BLENGTH(EntityTable)))),
m_TableBIDs(Vector<EntityBID>(CEIL4KB(ENTITY_TABLE_LIMIT * BLENGTH(EntityBID))))
{
	for (size_t i = 0; i < m_Events.Length(); ++i)
		new(&m_Events[i]) EntityContainer((i + 1) << 3, true);
	for (size_t i = 0; i < m_Events.Length(); ++i)
		m_Events[i].Grow();
	for (size_t i = 0; i < m_EventFunctions.Length(); ++i)
		m_EventFunctions[i].EmplaceBack((EventFunction)nullptr);

}
EntityEngine::~EntityEngine()
{
	for (size_t i = 0; i < EntitiesLength(); ++i) {
		EntityPointer& entity_pointer = m_Entities[i];
		Entity entity;
		entity.EntityID = i;
		entity.EntityVersion = entity_pointer.EntityVersion;
		if (entity_pointer.EntityTableID != 0b1111111111111111)
			DestroyEntity(entity);

	}

}

void EntityEngine::OnFrame(float delta_time)
{
	for (size_t i = 0; i < FrameLength(); ++i)
		s_FrameFunctions[i](*this, delta_time);

}
void EntityEngine::OnPeriodic(float delta_time)
{
	for (size_t i = 0; i < PeriodicLength(); ++i)
		s_PeriodicFunctions[i](*this, delta_time);

}
void EntityEngine::OnEvent()
{
	for (size_t i = 0; i < m_Events.Length(); ++i) {
		for (size_t j = m_Events[i].Length() - 1; j >= 1; --j) {
			m_EventFunctions[i][j](*this, m_Events[i][j]);
			m_Events[i].Shrink(j);
			m_EventFunctions[i].RemoveBack();

		}

	}

}

size_t EntityEngine::EntitiesLength()
{
	return m_Entities.Length();

}
size_t EntityEngine::TablesLength()
{
	return m_Tables.Length();

}
size_t EntityEngine::EventsLength()
{
	size_t length = 0;
	for (size_t i = 0; i < m_Events.Length(); ++i) {
		length += m_Events[i].Length() - 1;

	}
	return length;

}



Entity EntityEngine::CreateEntity()
{
	uint16_t table_id = TableWith<>();
	EntityTable& table = m_Tables[table_id];

	if (m_FreeEntityIDs.Length() > 0) {
		uint32_t entity_id = m_FreeEntityIDs[m_FreeEntityIDs.Length() - 1];
		m_FreeEntityIDs.RemoveBack();
		EntityPointer& entity_pointer = m_Entities[entity_id];
		entity_pointer.EntityTableID = table_id;
		entity_pointer.EntityVersion += 1;
		entity_pointer.EntityRecord = table.m_Entities.Length();
		
		Entity& entity = table.m_Entities.EmplaceBack();
		entity.EntityID = entity_id;
		entity.EntityVersion = entity_pointer.EntityVersion;
		return entity;

	}
	else {
		uint32_t entity_id = m_Entities.Length();
		EntityPointer& entity_pointer = m_Entities.EmplaceBack();
		entity_pointer.EntityTableID = table_id;
		entity_pointer.EntityVersion = 0;
		entity_pointer.EntityRecord = table.m_Entities.Length();

		Entity& entity = table.m_Entities.EmplaceBack();
		entity.EntityID = entity_id;
		entity.EntityVersion = entity_pointer.EntityVersion;
		return entity;

	}

}
void EntityEngine::DestroyEntity(Entity entity)
{
	EntityErrors(entity);
	EntityPointer& entity_pointer = m_Entities[entity.EntityID];

	EntityTable& table = m_Tables[entity_pointer.EntityTableID];
	EntityBID& table_bid = m_TableBIDs[entity_pointer.EntityTableID];
	entity_pointer.EntityTableID = 0b1111111111111111;
	m_FreeEntityIDs.PushBack(entity.EntityID);

	table.m_Entities.Remove(entity_pointer.EntityRecord);
	if (entity_pointer.EntityRecord != table.m_Entities.Length()) {
		Entity& other_entity = table.m_Entities[entity_pointer.EntityRecord];
		EntityPointer& other_entity_pointer = m_Entities[other_entity.EntityID];
		other_entity_pointer.EntityRecord = entity_pointer.EntityRecord;
	
	}
	// TODO: Could be Faster
	for (size_t fragment_id = 0; fragment_id < FragmentsLength(); ++fragment_id) {
		if (table_bid[fragment_id] && s_DestroyFunctions[fragment_id] != nullptr) {
			EntityContainer& entity_container = table.m_EntityContainers[fragment_id];
			s_DestroyFunctions[fragment_id](entity_container[entity_pointer.EntityRecord]);
			entity_container.Shrink(entity_pointer.EntityRecord);

		}

	}

}
bool EntityEngine::VerifyEntity(Entity entity)
{
	if (entity.EntityID >= EntitiesLength()) return false;
	EntityPointer& entity_pointer = m_Entities[entity.EntityID];
	return entity.EntityVersion == entity_pointer.EntityVersion && entity_pointer.EntityTableID != 0b1111111111111111;

}
uint16_t EntityEngine::FindTable(const EntityBID& search_table_bid)
{
	for (size_t table_id = 0; table_id < TablesLength(); ++table_id)
		if (m_TableBIDs[table_id] == search_table_bid) return table_id;
	
	uint16_t table_id = TablesLength();
	THROW(table_id == ENTITY_TABLE_LIMIT, std::length_error, "Entity Table Limit is Reached");
	EntityTable& entity_table = m_Tables.EmplaceBack();
	EntityBID& table_bid = m_TableBIDs.EmplaceBack();
	table_bid = search_table_bid;

	for (size_t fragment_id = 0; fragment_id < FragmentsLength(); ++fragment_id)
		if (search_table_bid[fragment_id]) entity_table.CreateContainer(s_FragmentBLengthBuffer[fragment_id], fragment_id, s_FragmentsIsData[fragment_id]);
	return table_id;

}

void EntityEngine::PrintEntities()
{
	size_t index = 0;
	for (size_t i = 0; i < EntitiesLength(); ++i) {
		EntityPointer& entity_pointer = m_Entities[i];
		Entity entity;
		entity.EntityID = i;
		entity.EntityVersion = entity_pointer.EntityVersion;
		if (entity_pointer.EntityTableID != 0b1111111111111111) {
			EntityBID& table_bid = m_TableBIDs[entity_pointer.EntityTableID];
			std::stringstream entity_log;
			entity_log << "E" << index << ":R" << entity_pointer.EntityRecord << ":V" << entity_pointer.EntityVersion << " { ";
			for (size_t fragment_id = 0; fragment_id < FragmentsLength(); ++fragment_id)
				if (table_bid[fragment_id])
					entity_log << "F" << fragment_id << "; ";
			entity_log << "}";
			LOG(entity_log.str());
			index += 1;

		}

	}
	LOG("");

}
void EntityEngine::PrintTables()
{
	for (size_t i = 0; i < TablesLength(); ++i) {
		EntityTable& table = m_Tables[i];
		EntityBID table_bid = m_TableBIDs[i];
		std::stringstream entity_log;
		entity_log << "T" << i << " { ";
		entity_log << "E:" << table.m_Entities.Length() << "; ";
		for (size_t fragment_id = 0; fragment_id < FragmentsLength(); ++fragment_id) {
			if (table_bid[fragment_id]) {
				entity_log << "F" << fragment_id << ":" << table.m_EntityContainers[fragment_id].Length() << "; ";
			
			}

		}
		entity_log << "}";
		LOG(entity_log.str());

	}
	LOG("");

}

void EntityEngine::EntityErrors(Entity entity)
{
	DEBUG_THROW(entity.EntityID >= EntitiesLength(), std::runtime_error, "Entity is not even created");
	EntityPointer& entity_pointer = m_Entities[entity.EntityID];
	DEBUG_THROW(entity.EntityVersion != entity_pointer.EntityVersion, std::runtime_error, "Entity is a dangling reference");
	DEBUG_THROW(entity_pointer.EntityTableID == 0b1111111111111111, std::runtime_error, "Entity is already destroyed");

}
