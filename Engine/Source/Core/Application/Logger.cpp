// Written by syri.
//
#include "Logger.h"


namespace Engine
{
	void Logger::Setup()
	{
		// Setup VT100/ANSI compatibility.
		HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD ConsoleMode = 0;
		GetConsoleMode(ConsoleHandle, &ConsoleMode);
		SetConsoleMode(ConsoleHandle, ConsoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	}

	std::string Logger::Print(LogType InLogType, std::string Message, bool ForceEndline)
	{
		// Output message type.
		if (InLogType == LogType::Info) fmt::print(fmt::fg(fmt::color::deep_sky_blue), "[INFO] ");
		else if (InLogType == LogType::Warning) fmt::print(fmt::fg(fmt::color::yellow), "[WARNING] ");
		else if (InLogType == LogType::Error) fmt::print(fmt::fg(fmt::color::red), "[ERROR] ");

		else if (InLogType == LogType::Success) fmt::print(fmt::fg(fmt::color::lime_green), "[SUCCESS] ");
		else if (InLogType == LogType::Failure) fmt::print(fmt::fg(fmt::color::red), "[FAILURE] ");

		// Output message.
		fmt::print(fmt::fg(fmt::color::white), Message);
		
		if (ForceEndline) std::cout << std::endl;

		return Message;
	}

	void Logger::Clear()
	{
#ifdef PRAE_PLATFORM_WINDOWS
		system("CLS");
#endif
	}
}
