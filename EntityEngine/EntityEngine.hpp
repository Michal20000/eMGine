#pragma once
#include <vector>

#include "EntityUtilities.hpp"
#include "EntityView.hpp"
#include "EntityFragment.hpp"
#include "EntityTable.hpp"



class EntityEngine
{
	public:
	friend class EntityView;
	template<class CLASS>
	static void Register();
	static size_t FrameLength();
	static size_t PeriodicLength();
	static size_t FragmentsLength();



	EntityEngine(Application& application);
	EntityEngine(const EntityEngine& ob) = delete;
	EntityEngine(EntityEngine&& ob) = delete;
	~EntityEngine();
	EntityEngine& operator=(const EntityEngine& ob) = delete;
	EntityEngine& operator=(EntityEngine&& ob) = delete;

	Application& GetApplication();
	size_t EntitiesLength();
	size_t TablesLength();
	size_t EventsLength();
	void OnFrame(float delta_time);
	void OnPeriodic(float delta_time);
	void OnEvent();

	template<class... BUFFER>
	Entity CreateEntity();
	Entity CreateEntity();
	void DestroyEntity(Entity entity);
	bool VerifyEntity(Entity entity);

	template<class... BUFFER>
	EntityView View();
	template<class CLASS, class... ARGUMENTS>
	CLASS& Dispatch(ARGUMENTS&&... arguments);
	template<class CLASS>
	void Attach(Entity entity);
	template<class CLASS>
	void Detach(Entity entity);
	template<class CLASS>
	bool VerifyFragment(Entity entity);
	template<class CLASS>
	CLASS& Fragment(Entity entity);

	void PrintEntities();
	void PrintTables();

	private:
	static Buffer<FrameFunction, ENTITY_FRAME_LIMIT> s_FrameFunctions;
	static Buffer<PeriodicFunction, ENTITY_PERIODIC_LIMIT> s_PeriodicFunctions;
	static size_t s_FrameLength;
	static size_t s_PeriodicLength;
	static uint16_t GenerateFragmentID();

	static Buffer<CreateFunction, ENTITY_FRAGMENT_LIMIT> s_CreateFunctions;
	static Buffer<CreateFunction, ENTITY_FRAGMENT_LIMIT> s_DestroyFunctions;
	static Buffer<size_t, ENTITY_FRAGMENT_LIMIT> s_FragmentBLengthBuffer;
	static Buffer<EntityBID, ENTITY_FRAGMENT_LIMIT> s_FragmentBIDs;
	static BitField<ENTITY_FRAGMENT_LIMIT> s_FragmentsIsData;
	static size_t s_FragmentsLength;



	Application& m_Application;
	Vector<EntityPointer> m_Entities;
	Vector<uint32_t> m_FreeEntityIDs;
	Vector<EntityTable> m_Tables;
	Vector<EntityBID> m_TableBIDs;
	Buffer<EntityContainer, 4> m_Events;
	Buffer<Vector<EventFunction>, 4> m_EventFunctions;

	template<class... BUFFER>
	uint16_t TableWith();
	// TODO: Errors; Private;
	template<class... BUFFER>
	uint16_t FindTable();
	template<class... BUFFER>
	std::vector<uint16_t>& TablesWith();
	// TODO: Errors; Private;
	template<class... BUFFER>
	std::vector<uint16_t> FindTables();
	// TODO: Verify;
	uint16_t FindTable(const EntityBID& search_table_bid);
	void EntityErrors(Entity entity);
	template<class CLASS>
	void FragmentErrors();

};



template<class CLASS>
void EntityEngine::Register()
{
	constexpr bool contains_create = requires {
		&CLASS::OnCreate == (void (*)(CLASS&))nullptr;

	};
	constexpr bool contains_destroy = requires {
		&CLASS::OnDestroy == (void (*)(CLASS&))nullptr;

	};
	constexpr bool contains_frame = requires {
		&CLASS::OnFrame == (void (*)(EntityEngine&, float))nullptr;

	};
	constexpr bool contains_periodic = requires {
		&CLASS::OnPeriodic == (void (*)(EntityEngine&, float))nullptr;

	};

	if constexpr (std::is_base_of<EntityFragment<CLASS>, CLASS>::value) {
		THROW(CLASS::s_InRegister, std::runtime_error, "Entity Data is already in Register");
		CLASS::s_BLength = CLASS::s_IsData ? BLENGTH(CLASS) : 0;
		CLASS::s_ID = GenerateFragmentID();
		CLASS::s_InRegister = true;
		s_FragmentBLengthBuffer[s_FragmentsLength] = CLASS::s_BLength;
		s_FragmentBIDs[s_FragmentsLength] = EntityBID();
		s_FragmentBIDs[s_FragmentsLength].True(CLASS::s_ID);
		if (CLASS::s_IsData) s_FragmentsIsData.True(CLASS::s_ID);
		else s_FragmentsIsData.False(CLASS::s_ID);
		s_FragmentsLength += 1;

		if constexpr (contains_create && CLASS::s_IsData) {
			s_CreateFunctions[s_FragmentsLength - 1] = (CreateFunction)&CLASS::OnCreate;
			LOG_VERBOSE("Function ::OnCreate found in " << typeid(CLASS).name());

		}
		else {
			s_CreateFunctions[s_FragmentsLength - 1] = (CreateFunction)nullptr;
			LOG_DEBUG("Function ::OnCreate not found in " << typeid(CLASS).name());

		}
		if constexpr (contains_destroy && CLASS::s_IsData) {
			s_DestroyFunctions[s_FragmentsLength - 1] = (DestroyFunction)&CLASS::OnDestroy;
			LOG_VERBOSE("Function ::OnDestroy found in " << typeid(CLASS).name());

		}
		else {
			s_DestroyFunctions[s_FragmentsLength - 1] = (DestroyFunction)nullptr;
			LOG_DEBUG("Function ::OnDestroy not found in " << typeid(CLASS).name());

		}

	}
	else {
		if constexpr (contains_frame) {
			THROW(s_FrameLength == ENTITY_FRAME_LIMIT, std::length_error, "Entity Engine can only contain " STRINGIFY(ENTITY_FRAME_LIMIT) " Frame Functions in Register");
			s_FrameFunctions[s_FrameLength++] = &CLASS::OnFrame;
			LOG_VERBOSE("Function ::OnFrame found in " << typeid(CLASS).name());

		}
		else LOG_DEBUG("Function ::OnFrame not found in " << typeid(CLASS).name());
		if constexpr (contains_periodic) {
			THROW(s_PeriodicLength == ENTITY_PERIODIC_LIMIT, std::length_error, "Entity Engine can only contain " STRINGIFY(ENTITY_PERIODIC_LIMIT) " Periodic Functions in Register");
			s_PeriodicFunctions[s_PeriodicLength++] = &CLASS::OnPeriodic;
			LOG_VERBOSE("Function ::OnPeriodic found in " << typeid(CLASS).name());

		}
		else LOG_DEBUG("Function ::OnPeriodic not found in " << typeid(CLASS).name());
		
	}

}



template<class... BUFFER>
EntityView EntityEngine::View()
{
	std::vector<uint16_t>& table_ids = TablesWith<BUFFER...>();
	EntityView view = EntityView(*this, &table_ids[0], &table_ids[table_ids.size()]);
	return view;

}
template<class CLASS, class... ARGUMENTS>
CLASS& EntityEngine::Dispatch(ARGUMENTS&&... arguments)
{
	constexpr bool contains_event = requires {
		&CLASS::OnEvent == (void (*)(EntityEngine&, CLASS&))nullptr;

	};
	size_t index = ((BLENGTH(CLASS) - 1) & ~7ULL) >> 3;

	DEBUG_THROW(contains_event == false, std::runtime_error, "Event class should have function OnEvent");
	DEBUG_THROW(BLENGTH(CLASS) > 32, std::runtime_error, "Event class BLength should not be greater than 32B");
	Vector<EventFunction>& event_functions = m_EventFunctions[index];
	EntityContainer& events = m_Events[index];

	event_functions.EmplaceBack((EventFunction)&CLASS::OnEvent);
	events.Grow();
	new(events[events.Length() - 1]) CLASS(std::forward<ARGUMENTS>(arguments)...);
	return *(CLASS*)events[events.Length() - 1];

}

template<class... BUFFER>
Entity EntityEngine::CreateEntity()
{
	uint16_t table_id = TableWith<BUFFER...>();
	EntityTable& table = m_Tables[table_id];
	// table.m_Containers[CLASS::ID()][entity_pointer.EntityRecord]
	// table.m_Containers[CLASS::ID()].Grow()
	// TODO: Grow containers + call OnCreate
	// s_CreateFunctions[CLASS::ID()]()
	// CLASS::IsData() ? Grow
	// (s_CreateFunctions[CLASS::ID()] != nullptr) ? 
	// s_CreateFunctions[CLASS::ID()](table.m_Containers[CLASS::ID()][entity_pointer.EntityRecord])
	// (void)((CLASS::IsData() ? (void)table.m_Containers[CLASS::ID()].Grow() : (void)nullptr), ..., (void)nullptr);
	// (void)(((s_CreateFunctions[CLASS::ID()] != nullptr) ? (void)s_CreateFunctions[CLASS::ID()](table.m_Containers[CLASS::ID()][entity_pointer.EntityRecord]) : (void)nullptr), ..., (void)nullptr);

	if (m_FreeEntityIDs.Length() > 0) {
		uint32_t entity_id = m_FreeEntityIDs[m_FreeEntityIDs.Length() - 1];
		m_FreeEntityIDs.RemoveBack();
		EntityPointer& entity_pointer = m_Entities[entity_id];
		entity_pointer.EntityTableID = table_id;
		entity_pointer.EntityVersion += 1;
		entity_pointer.EntityRecord = table.m_Entities.Length();
		
		// TODO: Verify;
		(void)((BUFFER::IsData() ? (void)table.m_EntityContainers[BUFFER::ID()].Grow() : (void)nullptr), ..., (void)nullptr);
		(void)(((s_CreateFunctions[BUFFER::ID()] != nullptr) ? (void)s_CreateFunctions[BUFFER::ID()](table.m_EntityContainers[BUFFER::ID()][entity_pointer.EntityRecord]) : (void)nullptr), ..., (void)nullptr);

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

		// TODO: Verify;
		(void)((BUFFER::IsData() ? (void)table.m_EntityContainers[BUFFER::ID()].Grow() : (void)nullptr), ..., (void)nullptr);
		(void)(((s_CreateFunctions[BUFFER::ID()] != nullptr) ? (void)s_CreateFunctions[BUFFER::ID()](table.m_EntityContainers[BUFFER::ID()][entity_pointer.EntityRecord]) : (void)nullptr), ..., (void)nullptr);

		Entity& entity = table.m_Entities.EmplaceBack();
		entity.EntityID = entity_id;
		entity.EntityVersion = entity_pointer.EntityVersion;
		return entity;

	}

}
template<class CLASS>
void EntityEngine::Attach(Entity entity)
{
	EntityErrors(entity);
	FragmentErrors<CLASS>();

	EntityPointer& entity_pointer = m_Entities[entity.EntityID];
	EntityTable& table = m_Tables[entity_pointer.EntityTableID];
	EntityBID& table_bid = m_TableBIDs[entity_pointer.EntityTableID];
	if (table_bid[CLASS::ID()] == true) return;

	if (table.m_AttachLookup[CLASS::ID()] != 0b1111111111111111) {
		LOG_WARN("Attach<> with Lookup");
		uint16_t table_id = table.m_AttachLookup[CLASS::ID()];
		EntityTable& attach_table = m_Tables[table_id];
		EntityBID& attach_bid = m_TableBIDs[table_id];

		table.m_Entities.Remove(entity_pointer.EntityRecord);
		if (entity_pointer.EntityRecord != table.m_Entities.Length()) {
			Entity& other_entity = table.m_Entities[entity_pointer.EntityRecord];
			EntityPointer& other_entity_pointer = m_Entities[other_entity.EntityID];
			other_entity_pointer.EntityRecord = entity_pointer.EntityRecord;
		
		}
		uint32_t before_record = entity_pointer.EntityRecord;
		entity_pointer.EntityTableID = table_id;
		entity_pointer.EntityRecord = attach_table.m_Entities.Length();
		Entity& reverse_entity = attach_table.m_Entities.EmplaceBack();
		reverse_entity = entity;
		
		for (size_t fragment_id = 0; fragment_id < FragmentsLength(); ++fragment_id) {
			if (table_bid[fragment_id] && s_FragmentsIsData[fragment_id]) {
				attach_table.m_EntityContainers[fragment_id].Grow();
				memcpy(attach_table.m_EntityContainers[fragment_id][entity_pointer.EntityRecord], table.m_EntityContainers[fragment_id][before_record], table.m_EntityContainers[fragment_id].m_ElementLength);
				table.m_EntityContainers[fragment_id].Shrink(before_record);

			}

		}
		if (CLASS::IsData()) {
			attach_table.m_EntityContainers[CLASS::ID()].Grow();
			if (s_CreateFunctions[CLASS::ID()] != nullptr)
				s_CreateFunctions[CLASS::ID()](attach_table.m_EntityContainers[CLASS::ID()][entity_pointer.EntityRecord]);

		}

	}
	else {
		LOG_WARN("Attach<> without Lookup");
		EntityBID attach_table_bid = table_bid;
		attach_table_bid.True(CLASS::ID());
		uint16_t table_id = FindTable(attach_table_bid);
		EntityTable& attach_table = m_Tables[table_id];
		EntityBID& attach_bid = m_TableBIDs[table_id];
		table.m_AttachLookup[CLASS::ID()] = table_id;
		attach_table.m_DetachLookup[CLASS::ID()] = entity_pointer.EntityTableID;
		
		table.m_Entities.Remove(entity_pointer.EntityRecord);
		if (entity_pointer.EntityRecord != table.m_Entities.Length()) {
			Entity& other_entity = table.m_Entities[entity_pointer.EntityRecord];
			EntityPointer& other_entity_pointer = m_Entities[other_entity.EntityID];
			other_entity_pointer.EntityRecord = entity_pointer.EntityRecord;
		
		}
		uint32_t before_record = entity_pointer.EntityRecord;
		entity_pointer.EntityTableID = table_id;
		entity_pointer.EntityRecord = attach_table.m_Entities.Length();
		Entity& reverse_entity = attach_table.m_Entities.EmplaceBack();
		reverse_entity = entity;
		
		for (size_t fragment_id = 0; fragment_id < FragmentsLength(); ++fragment_id) {
			if (table_bid[fragment_id] && s_FragmentsIsData[fragment_id]) {
				attach_table.m_EntityContainers[fragment_id].Grow();
				memcpy(attach_table.m_EntityContainers[fragment_id][entity_pointer.EntityRecord], table.m_EntityContainers[fragment_id][before_record], table.m_EntityContainers[fragment_id].m_ElementLength);
				table.m_EntityContainers[fragment_id].Shrink(before_record);

			}

		}
		if (CLASS::IsData()) {
			attach_table.m_EntityContainers[CLASS::ID()].Grow();
			if (s_CreateFunctions[CLASS::ID()] != nullptr)
				s_CreateFunctions[CLASS::ID()](attach_table.m_EntityContainers[CLASS::ID()][entity_pointer.EntityRecord]);

		}

	}

}
template<class CLASS>
void EntityEngine::Detach(Entity entity)
{
	EntityErrors(entity);
	FragmentErrors<CLASS>();

	EntityPointer& entity_pointer = m_Entities[entity.EntityID];
	EntityTable& table = m_Tables[entity_pointer.EntityTableID];
	EntityBID& table_bid = m_TableBIDs[entity_pointer.EntityTableID];
	if (table_bid[CLASS::ID()] == false) return;

	if (table.m_DetachLookup[CLASS::ID()] != 0b1111111111111111) {
		LOG_WARN("Detach<> with Lookup");
		uint16_t table_id = table.m_DetachLookup[CLASS::ID()];
		EntityTable& detach_table = m_Tables[table_id];
		EntityBID& detach_bid = m_TableBIDs[table_id];

		table.m_Entities.Remove(entity_pointer.EntityRecord);
		if (entity_pointer.EntityRecord != table.m_Entities.Length()) {
			Entity& other_entity = table.m_Entities[entity_pointer.EntityRecord];
			EntityPointer& other_entity_pointer = m_Entities[other_entity.EntityID];
			other_entity_pointer.EntityRecord = entity_pointer.EntityRecord;
		
		}
		uint32_t before_record = entity_pointer.EntityRecord;
		entity_pointer.EntityTableID = table_id;
		entity_pointer.EntityRecord = detach_table.m_Entities.Length();
		Entity& reverse_entity = detach_table.m_Entities.EmplaceBack();
		reverse_entity = entity;
		
		if (CLASS::IsData()) {
			if (s_DestroyFunctions[CLASS::ID()] != nullptr)
				s_DestroyFunctions[CLASS::ID()](table.m_EntityContainers[CLASS::ID()][before_record]);
			table.m_EntityContainers[CLASS::ID()].Shrink(before_record);

		}
		for (size_t fragment_id = 0; fragment_id < FragmentsLength(); ++fragment_id) {
			if (detach_bid[fragment_id] && s_FragmentsIsData[fragment_id]) {
				detach_table.m_EntityContainers[fragment_id].Grow();
				memcpy(detach_table.m_EntityContainers[fragment_id][entity_pointer.EntityRecord], table.m_EntityContainers[fragment_id][before_record], table.m_EntityContainers[fragment_id].m_ElementLength);
				table.m_EntityContainers[fragment_id].Shrink(before_record);

			}

		}

	}
	else {
		LOG_WARN("Detach<> without Lookup");
		EntityBID detach_table_bid = table_bid;
		detach_table_bid.False(CLASS::ID());
		uint16_t table_id = FindTable(detach_table_bid);
		EntityTable& detach_table = m_Tables[table_id];
		EntityBID& detach_bid = m_TableBIDs[table_id];
		table.m_DetachLookup[CLASS::ID()] = table_id;
		detach_table.m_AttachLookup[CLASS::ID()] = entity_pointer.EntityTableID;

		table.m_Entities.Remove(entity_pointer.EntityRecord);
		if (entity_pointer.EntityRecord != table.m_Entities.Length()) {
			Entity& other_entity = table.m_Entities[entity_pointer.EntityRecord];
			EntityPointer& other_entity_pointer = m_Entities[other_entity.EntityID];
			other_entity_pointer.EntityRecord = entity_pointer.EntityRecord;
		
		}
		uint32_t before_record = entity_pointer.EntityRecord;
		entity_pointer.EntityTableID = table_id;
		entity_pointer.EntityRecord = detach_table.m_Entities.Length();
		Entity& reverse_entity = detach_table.m_Entities.EmplaceBack();
		reverse_entity = entity;

		if (CLASS::IsData()) {
			if (s_DestroyFunctions[CLASS::ID()] != nullptr)
				s_DestroyFunctions[CLASS::ID()](table.m_EntityContainers[CLASS::ID()][before_record]);
			table.m_EntityContainers[CLASS::ID()].Shrink(before_record);
			
		}
		for (size_t fragment_id = 0; fragment_id < FragmentsLength(); ++fragment_id) {
			if (detach_bid[fragment_id] && s_FragmentsIsData[fragment_id]) {
				detach_table.m_EntityContainers[fragment_id].Grow();
				memcpy(detach_table.m_EntityContainers[fragment_id][entity_pointer.EntityRecord], table.m_EntityContainers[fragment_id][before_record], table.m_EntityContainers[fragment_id].m_ElementLength);
				table.m_EntityContainers[fragment_id].Shrink(before_record);

			}

		}

	}

}
template<class CLASS>
bool EntityEngine::VerifyFragment(Entity entity)
{
	// TODO: think about it
	if (entity.EntityID >= EntitiesLength()) return false;
	EntityPointer& entity_pointer = m_Entities[entity.EntityID];
	if (entity.EntityVersion != entity_pointer.EntityVersion) return false;
	if (entity_pointer.EntityTableID == 0b1111111111111111) return false;
	EntityBID& table_bid = m_TableBIDs[entity_pointer.EntityTableID];
	return table_bid[CLASS::ID()];

}
template<class CLASS>
CLASS& EntityEngine::Fragment(Entity entity)
{
	EntityErrors(entity);
	FragmentErrors<CLASS>();
	
	EntityPointer& entity_pointer = m_Entities[entity.EntityID];
	EntityTable& entity_table = m_Tables[entity_pointer.EntityTableID];
	EntityBID& table_bid = m_TableBIDs[entity_pointer.EntityTableID];
	DEBUG_THROW(CLASS::IsData() == false, std::runtime_error, "Entity Group does not have data");
	DEBUG_THROW(table_bid[CLASS::ID()] == false, std::runtime_error, "Entity should contain given Fragment");

	EntityContainer& container = entity_table.m_EntityContainers[CLASS::ID()];
	return *(CLASS*)container[entity_pointer.EntityRecord];

}
template<class CLASS>
CLASS& EntityView::Fragment()
{
	m_EntityEngine.FragmentErrors<CLASS>();
	EntityTable& table = m_EntityEngine.m_Tables[*m_TableCurrent];
	EntityBID& table_bid = m_EntityEngine.m_TableBIDs[*m_TableCurrent];
	DEBUG_THROW(CLASS::IsData() == false, std::runtime_error, "Entity Group does not have data");
	DEBUG_THROW(table_bid[CLASS::ID()] == false, std::runtime_error, "Entity should contain given Fragment");

	EntityContainer& container = table.m_EntityContainers[CLASS::ID()];
	return *(CLASS*)container[m_RecordCurrent];

}



// TODO: Errors;
template<class... BUFFER>
uint16_t EntityEngine::TableWith()
{
	static uint16_t table_id = FindTable<BUFFER...>();
	return table_id;

}
// TODO: Errors;
template<class... BUFFER>
uint16_t EntityEngine::FindTable()
{
	// TODO: Detect Errors in BUFFER
	// THROW((!BUFFER::InRegister() | ... | false), std::runtime_error, "Entity Fragments should be in Register");
	EntityBID bit_field; bit_field.Fill(0);
	EntityBID search_table_bid = (s_FragmentBIDs[BUFFER::ID()] | ... | bit_field);
	for (size_t search_table_id = 0; search_table_id < TablesLength(); ++search_table_id)
		if (search_table_bid == m_TableBIDs[search_table_id])
			return search_table_id;
	
	uint16_t table_id = TablesLength();
	THROW(table_id == ENTITY_TABLE_LIMIT, std::length_error, "Entity Table Limit is Reached");
	EntityTable& entity_table = m_Tables.EmplaceBack();
	EntityBID& table_bid = m_TableBIDs.EmplaceBack();
	table_bid = search_table_bid;

	(void)((void)entity_table.CreateContainer<BUFFER>(), ..., (void)nullptr);
	return table_id;

}
template<class... BUFFER>
std::vector<uint16_t>& EntityEngine::TablesWith()
{
	static std::vector<uint16_t> table_ids = FindTables<BUFFER...>();
	static size_t tables_length = TablesLength();
	if (tables_length != TablesLength()) [[unlikely]] {
		table_ids = FindTables<BUFFER...>();
		tables_length = TablesLength();

	}
	return table_ids;

}
template<class... BUFFER>
std::vector<uint16_t> EntityEngine::FindTables()
{
	// TODO: Detect Errors in BUFFER
	// THROW((!BUFFER::InRegister() | ... | false), std::runtime_error, "Entity Fragments should be in Register");
	std::vector<uint16_t> table_ids = std::vector<uint16_t>();
	table_ids.reserve(16);
	EntityBID bit_field; bit_field.Fill(0);
	EntityBID search_table_bid = (s_FragmentBIDs[BUFFER::ID()] | ... | bit_field);
	for (size_t table_id = 0; table_id < TablesLength(); ++table_id) {
		EntityBID& table_bid = m_TableBIDs[table_id];
		if ((table_bid & search_table_bid) == search_table_bid)
			table_ids.push_back(table_id);

	}
	return table_ids;

}



template<class CLASS>
void EntityEngine::FragmentErrors()
{
	bool condition = std::is_base_of<EntityFragment<CLASS>, CLASS>::value == false;
	DEBUG_THROW(condition, std::runtime_error, "Given Fragment should be derived from EntityFragment or EntityGroup");
	DEBUG_THROW(CLASS::InRegister() == false, std::runtime_error, "Given Fragment should be in Register");

}
