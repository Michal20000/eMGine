#include "Timer.hpp"



Timer::Timer(const std::string& name)
{
	mName = name;
	mBefore = std::chrono::steady_clock::now();

}
Timer::~Timer()
{
	mAfter = std::chrono::steady_clock::now();
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(mAfter - mBefore).count();
	auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(mAfter - mBefore).count();
	std::cout << mName << ".\n" << std::flush;
	std::cout << "Microseconds = " << microseconds << ".\n" << std::flush;
	std::cout << "Nanoseconds = " << nanoseconds << ".\n\n" << std::flush;

}
