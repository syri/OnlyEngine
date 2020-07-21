// Written by syri.
//
#include "Logger.h"


namespace Engine
{
	bool CLogger::s_Initialised = false;

	void CLogger::Setup()
	{
		// Setup VT100 / ANSI compatibility.
		HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD ConsoleMode = 0;
		GetConsoleMode(ConsoleHandle, &ConsoleMode);
		SetConsoleMode(ConsoleHandle, ConsoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	}

	void CLogger::Clear()
	{
#ifdef UMA_PLATFORM_WINDOWS
		std::system("CLS");
#else
		std::system("clear");
#endif
	}
}
