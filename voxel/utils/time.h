#pragma once
#include <chrono>
#include <time.h>

using std::chrono::system_clock;
using std::chrono::time_point;
using std::chrono::duration;

using seconds = std::ratio<1>;
using milliseconds = std::milli;
using microseconds = std::micro;
using nanoseconds = std::nano;


class TimeManager {
public:
	TimeManager() = default;

	template <typename T = seconds>
	double get_delta_time();
	
	template <typename T = seconds>
	double get_time();

protected:
	system_clock _clock;
	time_point<system_clock> _start = _clock.now();

	double _last_time = 0.0f;
};

template<typename T>
inline double TimeManager::get_delta_time()
{
	auto time = this->get_time<T>();
	auto delta_time = time - _last_time;

	_last_time = time;
	return delta_time;
}

template<typename T>
inline double TimeManager::get_time()
{
	duration<double> dur = system_clock::now() - _start;	
	auto time = std::chrono::duration_cast<duration<double, T>>(dur);
	auto count = time.count();

	return count;
}
