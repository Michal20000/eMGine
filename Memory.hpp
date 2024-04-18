#pragma once
#include <cstdint>



#define KB(X) ((X) * 1024)
#define MB(X) ((X) * 1024 * 1024)
#define GB(X) ((X) * 1024 * 1024 * 1024)

// TODO: VMemory Errors should use "std::bad_alloc"
// Function that will
// gather analytics data
// Functions for analitycs
// e.g. total_memory_allocated, allocations, deallocations

void* VReserve(size_t size);
void VFree(void* pointer, size_t length);
void VAllocate(void* pointer, size_t length);
void VDeallocate(void* pointer, size_t length);

// void Allocate();
// void Deallocate();
// void Reallocate();
