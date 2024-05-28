#pragma once
#include <chrono>
#include <iostream>



class Time
{
	public:

	private:
	

};
struct Timer
{
	private:
	std::string mName;
	std::chrono::steady_clock::time_point mBefore;
	std::chrono::steady_clock::time_point mAfter;

	public:
	Timer(const std::string&);
	~Timer();

};
