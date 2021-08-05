#pragma once

#define NOMINMAX

#ifdef ENGINE_PLATFORM_WINDOWS
	#ifdef BUILD_ENGINE_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif // BUILD_ENGINE_DLL
#else
	#error Not implemented supports for this platform!
#endif // ENGINE_PLATFORM_WINDOWS
