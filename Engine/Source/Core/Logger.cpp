// Written by Syri.
//
#include "Logger.h"


namespace Engine
{
	Logger::Logger()
	{
		m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	Logger::~Logger()
	{}

	std::string Logger::Print(LogType MessageType, std::string Message, bool ForceNewline)
	{
		// Output message type.
		SetConsoleTextAttribute(m_ConsoleHandle, (WORD)MessageType);
		if (MessageType == LogType::Info) std::cout << "[Info] ";
		else if (MessageType == LogType::Warning) std::cout << "[Warning] ";
		else if (MessageType == LogType::Error) std::cout << "[Error] ";

		// Output message.
		SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::cout << Message;
		
		if (ForceNewline) std::cout << std::endl;

		return Message;
	}

	void Logger::Clear()
	{
#ifdef ENGINE_PLATFORM_WINDOWS
		system("CLS");
#endif
	}
}
