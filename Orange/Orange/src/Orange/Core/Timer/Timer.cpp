#include "pchOrange.h"
#include "Timer.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


namespace Orange
{
	Timer::Timer()
	{
		this->Restart();
	}

	void Timer::Restart()
	{
		m_Start = std::chrono::high_resolution_clock::now();
	}

	void Timer::Wait(uint32_t ms)
	{
		Sleep(ms);
	}

	uint64_t Timer::GetMicroseconds() const
	{
		double seconds = GetSeconds(6);
		return (unsigned long long)(seconds * 1000000);
	}

	double Timer::GetMilliseconds(uint32_t precision) const
	{
		double seconds = GetSeconds(precision + 3);
		return seconds * 1000;
	}

	double Timer::GetSeconds(uint32_t precision) const
	{
		auto end = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> duration = end - m_Start;

		double power = std::pow(10, precision);
		return (duration.count() * power) / power;
	}

	std::string Timer::MicrosecondsToString() const
	{
		return Math::ToString(GetMicroseconds()) + (char)230 + "s";
	}

	std::string Timer::MillisecondsToString(uint32_t precision) const
	{
		return Math::ToString(GetMilliseconds(precision)) + "ms";
	}

	std::string Timer::SecondsToString(uint32_t precision) const
	{
		return Math::ToString(GetSeconds(precision)) + "s";
	}
}