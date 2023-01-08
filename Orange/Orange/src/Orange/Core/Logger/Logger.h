#pragma once
#include "spdlog/logger.h"


namespace Orange
{
	class Logger
	{
		Logger() {}
	public:
		Logger(const Logger&) = delete;
		static void Initialize();
		static std::shared_ptr<spdlog::logger> GetCore();
		static std::shared_ptr<spdlog::logger> GetClient();
	private:
		static std::shared_ptr<spdlog::logger> s_Core;
		static std::shared_ptr<spdlog::logger> s_Client;
	};
}