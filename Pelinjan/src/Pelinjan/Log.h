#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace Pelinjan
{
	class PE_API Log
	{
	public:
		static void Init();

		// create member functions to access the loggers
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		// create shared pointers for core and client logger
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros	
#define PE_CORE_TRACE(...)   ::Pelinjan::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PE_CORE_INFO(...)    ::Pelinjan::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PE_CORE_WARN(...)    ::Pelinjan::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PE_CORE_ERROR(...)   ::Pelinjan::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PE_CORE_FATAL(...)   ::Pelinjan::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define PE_TRACE(...) ::Pelinjan::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PE_INFO(...)  ::Pelinjan::Log::GetClientLogger()->info(__VA_ARGS__)
#define PE_WARN(...)  ::Pelinjan::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PE_ERROR(...) ::Pelinjan::Log::GetClientLogger()->error(__VA_ARGS__)
#define PE_FATAL(...) ::Pelinjan::Log::GetClientLogger()->fatal(__VA_ARGS__)



