#pragma once


namespace Orange
{
	class Timer
	{
	public:
		Timer();
		~Timer() = default;

		void Restart();

		uint64_t GetMicroseconds() const;
		double GetMilliseconds(uint32_t precision = 2) const;
		double GetSeconds(uint32_t precision = 2) const;
		std::string MicrosecondsToString() const;
		std::string MillisecondsToString(uint32_t precision = 2) const;
		std::string SecondsToString(uint32_t precision = 2) const;
		
		static void Wait(uint32_t ms);
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};
}

#define SLEEP(ms) Tomato::Timer::Wait(ms)
