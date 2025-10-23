#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace ChengboStudio 
{
	class CHENGBO_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define CB_CORE_ERROR(...) ::ChengboStudio::Log::GetCoreLogger()->error(__VA_ARGS__);
#define CB_CORE_WARN(...) ::ChengboStudio::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define CB_CORE_INFO(...) ::ChengboStudio::Log::GetCoreLogger()->info(__VA_ARGS__);
#define CB_CORE_TRACE(...) ::ChengboStudio::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define CB_CORE_FATAL(...) ::ChengboStudio::Log::GetCoreLogger()->fatal(__VA_ARGS__);

#define CB_ERROR(...) ::ChengboStudio::Log::GetClientLogger()->error(__VA_ARGS__);
#define CB_WARN(...) ::ChengboStudio::Log::GetClientLogger()->warn(__VA_ARGS__);
#define CB_INFO(...) ::ChengboStudio::Log::GetClientLogger()->info(__VA_ARGS__);
#define CB_TRACE(...) ::ChengboStudio::Log::GetClientLogger()->trace(__VA_ARGS__);
#define CB_FATAL(...) ::ChengboStudio::Log::GetClientLogger()->fatal(__VA_ARGS__);