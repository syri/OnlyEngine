// Written by syri.
//
#pragma once


#ifdef PRAESEGMEN_PLATFORM_WINDOWS
	#ifdef PRAESEGMEN_BUILD_DLL
		#define PRAESEGMEN_API __declspec(dllexport)
	#else
		#define PRAESEGMEN_API __declspec(dllimport)
	#endif
#else
	#error "Unsupported Platform Found!"
#endif
