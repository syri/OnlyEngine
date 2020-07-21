// Written by syri.
//
#pragma once


#ifdef UMA_PLATFORM_WINDOWS
	#ifdef UMA_BUILD_DLL
		#define UMA_API __declspec(dllexport)
	#else
		#define UMA_API __declspec(dllimport)
	#endif
#else
	#error "Unsupported Platform Found!"
#endif
