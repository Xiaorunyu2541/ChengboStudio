#pragma once
#ifdef STUDIO_WINDOWS_PLATFORM
	#ifdef STUDIO_DYNAMIC_BUILD
		#ifdef STUDIO_APP
			#define CHENGBO_API __declspec(dllimport)
		#else
			#define CHENGBO_API __declspec(dllexport)
		#endif
	#else
		#define CHENGBO_API
	#endif
#else
#error ChengboStudio only supports Windows (currently)
#endif

#define BIT(x) (1 << x) //Shift 00000001 for x places

#include "Log.h"

#ifdef DEBUG_ASSERTS
	#ifdef STUDIO_WINDOWS_PLATFORM
		#define CB_CORE_ASSERT(x, ...) { if (!(x)) { CB_CORE_ERROR("Assert failed! Error: {0}", __VA_ARGS__); __debugbreak; } }
		#define CB_ASSERT(x, ...) { if (!(x)) { CB_ERROR("Assert failed! Error: {0}", __VA_ARGS__); __debugbreak; } }
	#endif
#else
	#define CB_CORE_ASSERT(x, ...)
	#define CB_ASSERT(x, ...)
#endif

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)