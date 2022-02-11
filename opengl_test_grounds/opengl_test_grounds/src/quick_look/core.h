#pragma once

#ifdef QUICK_LOOK_WINDOWS_ENVIRONMENT
	#ifdef QUICK_LOOK_BUILD_DLL
		#define AS_QUICK_LOOK_API __declspec(dllexport)
	#else
		#define AS_QUICK_LOOK_API __declspec(dllimport)
	#endif

#else
	#error Quick look is only buildable on Windows.

#endif
