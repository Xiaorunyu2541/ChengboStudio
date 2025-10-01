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