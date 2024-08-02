#include "Time.hpp"
#include <chrono>



int64_t Time::s_Before = 0;
float Time::s_DeltaTime = 0.0F;



int64_t Time::Now()
{
	std::chrono::steady_clock::time_point time_point = std::chrono::steady_clock::now();
	int64_t now = *(int64_t*)&time_point;
	return now;

}
float Time::Duration(int64_t before, int64_t after)
{
	using time_point_t = std::chrono::steady_clock::time_point;
	time_point_t time_point_before = *(time_point_t*)&before;
	time_point_t time_point_after = *(time_point_t*)&after;

	int64_t nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(time_point_after - time_point_before).count();
	float duration = nanoseconds / 1000000000.0F;
	return duration;

}
float Time::FrameTime()
{
	return s_DeltaTime;

}
float Time::PeriodicTime()
{
	return 0.0F;

}
