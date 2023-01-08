#include "pchOrange.h"
#include "Logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"


namespace Orange
{
	std::shared_ptr<spdlog::logger> Logger::s_Core = nullptr;
	std::shared_ptr<spdlog::logger> Logger::s_Client = nullptr;
	void Logger::Initialize()
	{
		s_Core = spdlog::stdout_color_mt("Orange");
		s_Client = spdlog::stdout_color_mt("Client");
	}

	std::shared_ptr<spdlog::logger> Logger::GetCore()
	{
		return s_Core;
	}

	std::shared_ptr<spdlog::logger> Logger::GetClient()
	{
		return s_Client;
	}
}