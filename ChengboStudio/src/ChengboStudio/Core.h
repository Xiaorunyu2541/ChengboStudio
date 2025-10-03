#pragma once
#ifdef STUDIO_WINDOWS_PLATFORM
	#ifdef STUDIO_APP
		#define  CHENGBO_API __declspec(dllimport)
	#else
		#define CHENGBO_API __declspec(dllexport)
	#endif
#else
#error ChengboStudio only supports Windows (currently)
#endif

#define BIT(x) (1 << x) //Shift 00000001 for x places

#ifdef DEBUG_ASSERTS
	#define CB_CORE_ASSERT(x, ...) { if (!(x)) { CB_CORE_ERROR("Assert failed! Error: {0}", __VA_ARGS__); __debugbreak; } }
	#define CB_ASSERT(x, ...) { if (!(x)) { CB_ERROR("Assert failed! Error: {0}", __VA_ARGS__); __debugbreak; } }
#elif
	#define CB_CORE_ASSERT(x, ...)
	#define CB_ASSERT(x, ...)
#endif