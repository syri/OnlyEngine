// Written by syri.
//
#pragma once


#ifdef PRAE_PLATFORM_WINDOWS
	#ifdef PRAE_BUILD_DLL
		#define PRAE_API __declspec(dllexport)
	#else
		#define PRAE_API __declspec(dllimport)
	#endif
#else
	#error "Unsupported Platform Found!"
#endif
