#pragma once
#include <cstdint>

#include "Buffer.hpp"
#include "Vector.hpp"
#include "BitField.hpp"
#include "Logs.hpp"
#include "Errors.hpp"



#define BLENGTH(X) sizeof(X)
#define DEFAULT_5_RULE(Class) Class() = default; Class(const Class& ob) = default; Class(Class&& ob) = default; ~Class() = default; Class& operator=(const Class& ob) = default; Class& operator=(Class&& ob) = default
#define STRINGIFY_BUFFER(X) #X
#define STRINGIFY(X) STRINGIFY_BUFFER(X)
#define CEIL4KB(X) ((X) + 4095ULL) & ~4095ULL

#define ENTITY_LIMIT 256ULL * 256ULL * 256ULL
#define ENTITY_IN_TABLE_LIMIT 256ULL * 256ULL * 16ULL
#define ENTITY_FRAME_LIMIT 64ULL
#define ENTITY_PERIODIC_LIMIT 64ULL
#define ENTITY_FRAGMENT_LIMIT 256ULL
#define ENTITY_TABLE_LIMIT 256ULL * 16ULL
// TODO: static_assert(...);
// TODO: ...

class Application;
class EntityEngine;
using CreateFunction = void (*)(void*);
using DestroyFunction = void (*)(void*);
using FrameFunction = void (*)(EntityEngine&, float);
using PeriodicFunction = void (*)(EntityEngine&, float);
using EventFunction = void (*)(EntityEngine&, void*);
using EntityBID = BitField<ENTITY_FRAGMENT_LIMIT>; // TODO: Destroy
// TODO: EntityField



struct Entity
{
	public:
	uint64_t EntityVersion : 16;
	uint64_t EntityID : 24;
	DEFAULT_5_RULE(Entity);

};

struct EntityPointer
{
	public:
	uint64_t EntityTableID : 16;
	uint64_t EntityVersion : 16;
	uint64_t EntityRecord : 24;
	DEFAULT_5_RULE(EntityPointer);

};
