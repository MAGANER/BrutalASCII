#include "Timer.h"



Timer::Timer(float max_seconds)
{
	max = seconds(max_seconds);
}
Timer::Timer(Int64 max_microseconds)
{
	max = microseconds(max_microseconds);
}
void Timer::restart()
{
	clock.restart();
}
void Timer::tic()
{
	elapsed = clock.getElapsedTime();
	if (elapsed.asMilliseconds() > max.asMilliseconds())
	{
		clock.restart();
	}
}
Time Timer::get_elapsed_time()
{
	return elapsed;
}
Time Timer::get_max_time()
{
	return max;
}
Timer::~Timer()
{
}
