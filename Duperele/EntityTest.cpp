#include <iostream>
#include <cstdint>
#include <array>
#include <unordered_map>
#include <exception>
#include "Timer.hpp"
#include "BitField.hpp"
#include "Vector.hpp"
#include "Buffer.hpp"
#include "Logs.hpp"
#include "Errors.hpp"
#include "EntityEngine.hpp"
#include <vector>
#include <set>
#include <algorithm>
#include <type_traits>
#include <conio.h>



// class Test// : public YY<33>
// {
// 	public:
// 	//void* ptr = (void*)16;
// 	uint64_t ptr = 16;
// 	uint16_t buff[40];

// 	// Test() = default; Test(const Test& ob) = default;
// 	// Test(Test&& ob) = default; ~Test() = default;

// 	Test() { LOG_DEBUG("Create"); }
// 	// Test() = default;
// 	Test(const Test& ob) { LOG_DEBUG("Copy"); }
// 	Test(Test&& ob) { LOG("Move"); ob.ptr = 0; }
// 	~Test() { if (ptr == 0) LOG("Nothing to Destroy"); else LOG_WARN("Destroy"); }
	
// 	// Test& operator=(const Test& ob) { LOG_DEBUG("Copy Assign"); return *this; }
// 	// Test& operator=(Test&& ob) { LOG("Move Assign"); ob.ptr = 0; return *this; }

// };


struct GF : public EntityGroup<GF>
{
	public:
	float vGF;

	static void OnCreate(GF& ob)
	{
		LOG("GF::OnCreate() called;");

	}
	static void OnDestroy(GF& ob)
	{
		LOG("GF::OnDestroy() called;");

	}

};
struct BF : public EntityFragment<BF>
{
	public:
	uint64_t B;
	uint64_t F;
	
	static void OnCreate(BF& ob)
	{
		ob.B = 0; ob.F = 0;
		LOG("BF::OnCreate() called;");

	}
	static void OnDestroy(BF& ob)
	{
		ob.B = 0; ob.F = 0;
		LOG("BF::OnDestroy() called;");

	}

};
struct Pos : public EntityFragment<Pos> { public: uint64_t X; uint64_t Y; };


template<size_t I>
class XY
{
	public:
	static void OnFrame(EntityEngine& ee, float delta_time)
	{
		for (auto view = ee.View<Pos>(); view.Verify(); ++view) {
			Entity entity = view.Record();
			Pos& pos = view.Fragment<Pos>();

			ECHO(entity.EntityID << " " << entity.EntityVersion);
			ECHO(pos.X << " " << pos.Y);
			LOG("");

		}

	}
	static void OnPeriodic(EntityEngine& ob, float delta_time)
	{
		LOG_FL_WARN("OnPeriodic in XY " << I);
		// ob.TablesWith<GF>();
		// LOG_FL_WARN("Delta time is " << delta_time);
		uint16_t table_id = ob.TableWith<GF, BF>();
		EntityTable& table = ob.m_Tables[table_id];

		Vector<Entity>& entities = table.m_Entities;
		EntityContainer& gfs = table.m_EntityContainers[GF::ID()];
		EntityContainer& bfs = table.m_EntityContainers[BF::ID()];
		size_t L = entities.Length();
		for (size_t i = 0; i < L; ++i) {
			Entity& e = entities[i];
			GF& gf = *(GF*)gfs[i];
			BF& bf = *(BF*)bfs[i];
			// bf.B += 1; bf.F += 3;
			LOG_SILLY("ID: " << e.EntityID << " = " << bf.B << " " << bf.F);
			LOG("");

		}
		ECHO_WARN(table_id);

	}

};



class CreateEnemyEvent
{
	public:
	uint64_t X;
	uint64_t Y;

	static void OnEvent(EntityEngine& ee, CreateEnemyEvent& event)
	{
		Entity entity = ee.CreateEntity();
		ee.Attach<Pos>(entity);
		Pos& pos = ee.Fragment<Pos>(entity);
		pos.X = event.X; pos.Y = event.Y;

	}

};
int32_t main()
{
	// TODO: 
	// TODO: ::Vector; ::Vector4KB; ::Vector16KB;
	// TODO: ::VectorBuffer; ::GenericVector4KB; ::GenericVector16KB;
	// TODO: ::Buffer; ::GenericBuffer;



	// TODO: EntityView& view = ee.View<...>();
	// TODO: for (; view.Verify(); ++view)
	// TODO: for (; view.Available(); ++view)
	// TODO: for (; view.Advanceable(); ++view)
	// TODO: view.Entity(); view.Fragment<...>();

	// TODO: Attach<> should return Ob&
	ECHO((((1 - 1) & ~7ULL) >> 3));
	ECHO((((7 - 1) & ~7ULL) >> 3));
	ECHO((((8 - 1) & ~7ULL) >> 3));
	ECHO((((9 - 1) & ~7ULL) >> 3));
	ECHO((((16 - 1) & ~7ULL) >> 3));
	ECHO((((17 - 1) & ~7ULL) >> 3));

	ECHO(BLENGTH(Entity));
	ECHO(BLENGTH(EntityPointer));

	EntityEngine::Register<GF>();
	EntityEngine::Register<BF>();
	EntityEngine::Register<Pos>();
	LOG("");
	using XY_0 = XY<0>;
	EntityEngine::Register<XY_0>();
	LOG("");

	EntityEngine entity_engine = EntityEngine();
	ECHO(entity_engine.EventsLength());
	entity_engine.Dispatch<CreateEnemyEvent>();
	entity_engine.Dispatch<CreateEnemyEvent>();
	entity_engine.Dispatch<CreateEnemyEvent>();
	ECHO(entity_engine.EventsLength());
	entity_engine.OnEvent();
	ECHO(entity_engine.EventsLength());
	Entity e = entity_engine.CreateEntity();
	entity_engine.Attach<Pos>(e);
	entity_engine.Attach<GF>(e);

	entity_engine.OnFrame(0.0F);
	getch();
	

	Entity e1 = entity_engine.CreateEntity();
	Entity e2 = entity_engine.CreateEntity();
	for (size_t i = 0; i < 5; ++i) {
		Entity e = entity_engine.CreateEntity();
		entity_engine.Attach<BF>(e);

	}
	ECHO_WARN(entity_engine.VerifyFragment<GF>(e1));
	ECHO_WARN(entity_engine.VerifyFragment<BF>(e1));
	ECHO(e1.EntityID); ECHO(e1.EntityVersion);

	entity_engine.Attach<GF>(e1);
	entity_engine.Attach<BF>(e1);
	entity_engine.Attach<BF>(e2);
	entity_engine.Attach<GF>(e2);
	entity_engine.PrintEntities();
	entity_engine.PrintTables();

	BF& bf = entity_engine.Fragment<BF>(e1);
	bf.B = 0.0; bf.F = 0.0;
	ECHO_WARN(entity_engine.VerifyFragment<GF>(e1));
	ECHO_WARN(entity_engine.VerifyFragment<BF>(e1));
	ECHO(entity_engine.TablesLength());

	entity_engine.Detach<GF>(e1);
	ECHO_WARN(entity_engine.VerifyFragment<GF>(e1));
	ECHO_WARN(entity_engine.VerifyFragment<BF>(e1));
	ECHO(entity_engine.TablesLength());

	entity_engine.Detach<GF>(e1);
	entity_engine.Detach<BF>(e2);
	ECHO(entity_engine.TablesLength());
	entity_engine.PrintEntities();
	entity_engine.PrintTables();



	// Fragment musi dziedziczyć po EntityFragment<...>
	// Fragment musi być zarejestrowany



	// Entity e2 = entity_engine.CreateEntity();
	// ECHO(e2.EntityID); ECHO(e2.EntityVersion);

	// ECHO(entity_engine.m_Entities.Length());
	// ECHO(entity_engine.m_Entities[e2.EntityID].EntityRecord);
	// entity_engine.DestroyEntity(e1);
	// ECHO(entity_engine.m_Entities.Length());
	// ECHO(entity_engine.m_Entities[e2.EntityID].EntityRecord);
	// LOG("");
	// entity_engine.DestroyEntity(e1);
	// Entity e3 = entity_engine.CreateEntity();
	// ECHO(entity_engine.m_Entities.Length());
	// ECHO(entity_engine.m_Entities[e3.EntityID].EntityRecord);
	// ECHO(e3.EntityID); ECHO(e3.EntityVersion);
	// entity_engine.DestroyEntity(e1);
	// LOG("");

	// entity_engine.Attach<GF>(e2);
	// entity_engine.Detach<GF>(e2);
	// entity_engine.Attach<BF>(e3);

	// uint16_t TableWith(const EntityBID& table_bid)

	

	
	// entity_engine.CreateEntity<GF>();
	// entity_engine.CreateEntity<BF>();
	// LOG_ERROR("----------------");
	// uint32_t entity_id_3 = entity_engine.CreateEntity<GF, BF>();
	// ECHO_ERROR(entity_engine.FragmentsLength());
	// ECHO_ERROR(entity_engine.TablesLength());
	// ECHO_ERROR(entity_engine.m_Entities[entity_id_3].EntityTableID);
	// ECHO_ERROR(entity_engine.m_Entities[entity_id_3].EntityRecord);
	// GF& gf = entity_engine.Fragment<GF>(entity_id_3);
	// BF& bf = entity_engine.Fragment<BF>(entity_id_3);
	// bf.B = 0; bf.F = 0;

	// ECHO_FL_ERROR("");
	// uint32_t entity_id_4 = entity_engine.CreateEntity<GF, BF>();
	// GF& gf1 = entity_engine.Fragment<GF>(entity_id_4);
	// BF& bf1 = entity_engine.Fragment<BF>(entity_id_4);
	// bf1.B = 10; bf1.F = 10;

	// ECHO_FL_ERROR("");
	// uint32_t entity_id_5 = entity_engine.CreateEntity<GF, BF>();
	// GF& gf2 = entity_engine.Fragment<GF>(entity_id_5);
	// BF& bf2 = entity_engine.Fragment<BF>(entity_id_5);
	// bf2.B = 110; bf2.F = 110;

	// entity_engine.CreateEntity<>();
	// entity_engine.CreateEntity<>();
	// entity_engine.CreateEntity<>();

	// LOG_ERROR("----------------");
	// uint32_t entity_id_5 = entity_engine.CreateEntity<>();
	// uint32_t entity_id_6 = entity_engine.CreateEntity<>();
	// ECHO(entity_engine.m_Entities[entity_id_5].EntityTableID);
	// ECHO(entity_engine.m_Entities[entity_id_5].EntityRecord);
	// ECHO(entity_engine.m_Entities[entity_id_6].EntityTableID);
	// ECHO(entity_engine.m_Entities[entity_id_6].EntityRecord);
	// GF& gf = entity_id_1.Fragment<GF>(entity_id_1);

	// uint32_t entity_id_2 = entity_engine.CreateEntity<BF>();
	// BF& gf = entity_id_1.Fragment<BF>(entity_id_2);

	// entity_engine.Attach<BF>(entity_id_1);
	// entity_engine.Attach<BF>(entity_id_2);
	// entity_engine.Detach<BF>(entity_id_1);
	// entity_engine.Detach<BF>(entity_id_2);

	// entity_engine.DestroyEntity(entity_id_1);
	// entity_engine.DestroyEntity(entity_id_2);

	// LOG_ERROR("----------------");
	// // getch();
	// entity_engine.Frame(0.0F);
	// entity_engine.Periodic(0.0F);

	// LOG_ERROR("----------------");
	// ECHO_WARN(entity_engine.EntitiesLength());
	// entity_engine.DestroyEntity(entity_id_4);
	// ECHO_WARN(entity_engine.EntitiesLength());
	
	// while (getch() != '0') {
	// 	entity_engine.Frame(0.0F);
	// 	entity_engine.Periodic(0.0F);

	// }
	// LOG_ERROR("----------------");
	// ECHO_ERROR(sizeof(EntityContainer));
	// EntityContainer ec = EntityContainer(64, true);
	// ec.Grow(); ec.Grow(); ECHO(ec.Length() << " " << ec.BLength() << "" << ec[ec.Length()]);
	// ec.Grow(); ec.Grow(); ECHO(ec.Length() << " " << ec.BLength() << "" << ec[ec.Length()]);
	// ec.Grow(); ECHO(ec.Length() << " " << ec.BLength() << "" << ec[ec.Length()]);
	// ec.Grow(); ECHO(ec.Length() << " " << ec.BLength() << "" << ec[ec.Length()]);
	// ec.Grow(); ECHO(ec.Length() << " " << ec.BLength() << "" << ec[ec.Length()]);
	// ec.Shrink(); ECHO(ec.Length() << " " << ec.BLength() << "" << ec[ec.Length()]);
	// ec.Shrink(); ECHO(ec.Length() << " " << ec.BLength() << "" << ec[ec.Length()]);
	// ec.Shrink(); ECHO(ec.Length() << " " << ec.BLength() << "" << ec[ec.Length()]);
	// ec.Grow(); ec.Grow(); ECHO(ec.Length() << " " << ec.BLength() << "" << ec[ec.Length()]);
	// // INFO: Structures
	// EntityEngine::Register<CFrame>();
	// EntityEngine::Register<Hello>();
	// LOG("");
	// // INFO: Handlers
	// EntityEngine::Register<Physics>();
	// LOG("");
	// ECHO(CFrame::ID());
	// ECHO(Hello::ID());



	// EntityEngine* entity_engine = new EntityEngine();
	// EntityID entity_id = entity_engine->PushEntity<CFrame, Hello>();


	// ECHO(sizeof(*entity_engine));
	// delete entity_engine;

// EntityEngine* ee = new EntityEngine();
// EntityID entity_id_1 = ee->PushEntity();
// EntityID entity_id_2 = ee->PushEntity<CFrame, Hello>(CFrame(0.0F, 0.0F, 0.0F));
// ee->RemoveEntity(entity_id_1);
	// sprawdzanie czy istnieje tabelka_CFrame_Hello
	// True -> Dodanie obiektu do instniejacej
	// False -> Stworzenie nowej + Dodanie

	// Bierzemy ID tabelki
	// Ustawiamy BitField komponentów
	// CFrame::BitField.True(TableID);
	// Hello::BitField.True(TableID);

	// ECHO(EntityEngine::CreateLength());
	// ECHO(EntityEngine::DestroyLength());
	// ECHO(EntityEngine::FrameLength());
	// ECHO(EntityEngine::PeriodicLength());

	// TODO: Dodawanie Entity
	// TODO: Usuwanie Entity
	// TODO: Dodawanie Komponentu
	// TODO: Usuwanie Komponentu
	// TODO: EntityBuilder
	// TODO: Indeksy i Relacje
	// TODO: Kolizje i Triggery
	// TODO: Eventy
	// TODO: Flagi i Tagi
	// TODO: Widoki jako Iteratory
	// TODO: Popularne problemy

// EntityView<CFrame, Hello> view = ee.View<CFrame, Hello>
// EntityTable& table; size_t index;
// CFrame& cframe = view.Return<CFrame>();
// Hello& cframe = view.Return<Hello>();



}
