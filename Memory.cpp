#include "Memory.hpp"
#include "Logs.hpp"
#include <cstdint>



// void* operator new(size_t size) {
// 	// Function can throw AllocationError if malloc fails
// 	// Function is not thread safe
// 	return (void*)(U8*)(32);

// }
// void* operator new[](size_t size) {
// 	// Function can throw AllocationError if malloc fails
// 	// Function is not thread safe
// 	return (void*)(U8*)(32);

// }
// void operator delete(void* pointer) noexcept {

// }
// void operator delete[](void* pointer) noexcept {

// }

// // Private member values
// // that will hold this values
// // Function that will
// // gather analytics data
// // Functions for analitycs
// // e.g. total_memory_allocated, allocations, deallocations

// template<size_t size>
// struct Chunk {
// 	public:

// 	private:
// 	Chunk* mNext;
// 	U8 mBuffer[size - sizeof(Chunk*)];

// };
// // Buckets: 1024B 512B 256B 128B 64B 32B 16B 8B
// // Biggest possible value: 256B
// using Chunk4KB = Chunk<KB(4)>;
// // Buckets: 1024KB 512KB 256KB 128KB 64KB 32KB 16KB 8KB
// // Biggest possible value: 256KB
// using Chunk4MB = Chunk<MB(4)>;
// // allocations like 64MB will be handled by malloc
// // Deallocate for chunks bigger than 256KB will be handled by malloc



// struct Block {
// 	public:
// 	// return (U8*)(Next()) - (U8*)(((U8*)this) + sizeof(Block*) + sizeof(Block*))
// 	size_t BlockSize();
// 	// return (bool)(mPrevious & 1);
// 	bool IsFree();
// 	// return mPrevious & ~7;
// 	Block* Previous();
// 	// return mNext & ~7;
// 	Block* Next();
// 	// return ((U8*)this) + sizeof(Block*) + sizeof(Block*)
// 	void* AllocationAddress();

// 	// Just set first bit
// 	void Free();
// 	// Just set first bit
// 	void Obtain();

// 	private:
// 	Block* mPrevious;
// 	Block* mNext;

// };



#if defined(_WIN32)
#include <memoryapi.h>
#include <errhandlingapi.h>

void* VReserve(size_t length)
{
	LOG_VERBOSE("VReserve: " << length << " " << (length >> 10));
	// TODO: profile data
	// TODO: error class GetLastError();
	struct VReserveError {}; // Main.cpp:33 Function mmap() fails with error code 
	void* reserve_pointer = VirtualAlloc(nullptr, length, MEM_RESERVE, PAGE_READWRITE);
	if (reserve_pointer == nullptr) [[unlikely]] throw VReserveError();
	return reserve_pointer;

}
void VFree(void* pointer, size_t length)
{
	LOG_VERBOSE("VFree: " << length << " " << (length >> 10));
	// TODO: profile data
	// TODO: error class GetLastError();
	struct VFreeError {}; // Main.cpp:33 Function "VAlloc" fails with error code 35
	int32_t error_code = VirtualFree(pointer, 0, MEM_RELEASE);
	if (error_code == 0) [[unlikely]] throw VFreeError();

}
void VAllocate(void* pointer, size_t length)
{
	LOG_VERBOSE("VAllocate: " << length << " " << (length >> 10));
	// TODO: profile data
	// TODO: error class GetLastError();
	struct VAllocateError {}; // Main.cpp:33 VAlloc returns 35
	void* allocate_pointer = VirtualAlloc(pointer, length, MEM_COMMIT, PAGE_READWRITE);
	if (allocate_pointer == nullptr) [[unlikely]] throw VAllocateError();

}
void VDeallocate(void* pointer, size_t length)
{
	LOG_VERBOSE("VDeallocate: " << length << " " << (length >> 10));
	// TODO: profile data
	// TODO: error class GetLastError();
	struct VDeallocateError {}; // Main.cpp:33 VAlloc returns 35
	int32_t error_code = VirtualFree(pointer, length, MEM_DECOMMIT);
	if (error_code == 0) [[unlikely]] throw VDeallocateError();

}
#elif defined(LINUX)
#include <sys/mman.h>
#include <errno.h>

void* VReserve(size_t size)
{
	// TODO: profile data
	// TODO: error class GetLastError();
	struct VReserveError {}; // Main.cpp:33 Function mmap() fails with error code 
	void* reserve_pointer = mmap(nullptr, size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (reserve_pointer == MAP_FAILED) [[unlikely]] throw VReserveError();
	return reserve_pointer;

}
void VFree(void* pointer, size_t size)
{
	// TODO: profile data
	// TODO: error class GetLastError();
	struct VFreeError {}; // Main.cpp:33 Function "munmap" fails with error code 35
	int32_t error_code = munmap(pointer, size);
	if (error_code != 0) [[unlikely]] throw VFreeError();

}
void VAllocate(void* pointer, size_t size)
{
	// TODO: profile data
	// TODO: error class GetLastError();
	struct VAllocateError {}; // Main.cpp:33 VAlloc returns 35
	int32_t error_code = mprotect(pointer, size, PROT_READ | PROT_WRITE);
	if (error_code != 0) [[unlikely]] throw VAllocateError();

}
void VDeallocate(void* pointer, size_t size)
{
	// TODO: profile data
	// TODO: error class GetLastError();
	struct VDeallocateError {}; // Main.cpp:33 VAlloc returns 35
	int32_t error_code = mprotect(pointer, size, PROT_NONE);
	if (error_code != 0) [[unlikely]] throw VAllocateError();
	
}
#else
#error Library supports only Windows and Linux
#endif



// void* Allocate(size_t size) {
// 	return nullptr;

// }
// void Deallocate(void* pointer) {

// }
// void Reallocate() {
// 	// ...

// }




