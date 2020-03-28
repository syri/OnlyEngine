// Written by syri.
//
#include "Logger.h"


namespace Engine
{
	std::string Logger::Print(LogType MessageType, std::string Message, bool ForceEndline)
	{
		// Setup VT100/ANSI compatibility.
		HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD ConsoleMode = 0;
		GetConsoleMode(ConsoleHandle, &ConsoleMode);
		ConsoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(ConsoleHandle, ConsoleMode);

		// Output message type.
		if (MessageType == LogType::Info) fmt::print(fmt::fg(fmt::color::deep_sky_blue), "[INFO] ");
		if (MessageType == LogType::Warning) fmt::print(fmt::fg(fmt::color::yellow), "[WARNING] ");
		if (MessageType == LogType::Error) fmt::print(fmt::fg(fmt::color::red), "[ERROR] ");

		if (MessageType == LogType::Success) fmt::print(fmt::fg(fmt::color::lime_green), "[SUCCESS] ");
		if (MessageType == LogType::Failure) fmt::print(fmt::fg(fmt::color::red), "[FAILURE] ");

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
