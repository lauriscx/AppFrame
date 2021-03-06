#pragma once
#include "Asserts.h"

#include <FileSystem>
#include <map>

#define quote(x) #x

#define NOMINMAX

#ifdef ENGINE_PLATFORM_WINDOWS
	#ifdef BUILD_ENGINE_DLL
		#define __declspec(dllexport)
	#else
		#define __declspec(dllimport)
	#endif // BUILD_ENGINE_DLL
#else
	//#error Not implemented supports for this platform!
#endif // ENGINE_PLATFORM_WINDOWS
