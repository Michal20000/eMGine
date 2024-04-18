#include <iostream>
#include <cstdint>
#include <array>
#include <unordered_map>
#include "Vector.hpp"
#include "Hello.hpp"
#include "Timer.hpp"
#include "BitField.hpp"
#include "Logs.hpp"
#include "Errors.hpp"
#include <vector>
#include <set>
#include <algorithm>



// uint64_t C0;
// uint64_t C0 = uint64_t(); uint64_t C0 = uint64_t(4);
// uint64_t C2 = C0;
// uint64_t C3 = (uint64_t&&)C0;
// DefaultConstructor = delete;
// WithParamsConstructors = delete;
// CopyConstructor = delete;
// MoveConstructor = delete;
class Test
{
	public:
	void* ptr = (void*)16;
	uint8_t buff[4088];
	Test() { LOG_DEBUG("Create"); }
	Test(const Test& ob) { LOG_DEBUG("Copy"); }
	Test(Test&& ob) { LOG("Move"); ob.ptr = nullptr; }
	~Test() { if (ptr == nullptr) LOG("Nothing to Destroy"); else LOG_WARN("Destroy"); }
	
	Test& operator=(const Test& ob) { LOG_DEBUG("Copy Assign"); return *this; }
	Test& operator=(Test&& ob) { LOG("Move Assign"); ob.ptr = nullptr; return *this; }

};



int main()
{
	Vector<Test> ints = Vector<Test>(4096 + 4096 + 4096 + 4096 + 4096 + 4096);
	ints.PushBack(Test());
	ints.Push(2, Test());
	
	// for (size_t i = 0; i < ints.Length(); ++i) LOG_WARN(ints.At(i)); LOG_WARN("");
	LOG("");
	ints.EmplaceBack(); ints.Remove(0); 

	LOG("");
	Vector<Test> ints2 = ints;
	ints2.EmplaceBack();
	LOG("");
	Vector<Test> ints3 = std::move(ints2);

	LOG("Powinny być 3 Vectory; 1 Pusty");
	LOG(ints.Begin()); LOG(ints2.Begin()); LOG(ints3.Begin());
	LOG(ints.Length()); LOG(ints2.Length()); LOG(ints3.Length());


	LOG("");
	ints2 = ints3;
	ints2.EmplaceBack();
	ints2.EmplaceBack();
	ints2.RemoveBack();
	LOG("");	
	
	LOG("Powinny być 3 Vectory; 0 Pustych");
	LOG(ints.Begin()); LOG(ints2.Begin()); LOG(ints3.Begin());
	LOG(ints.Length()); LOG(ints2.Length()); LOG(ints3.Length());

}
