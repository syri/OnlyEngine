// Written by Syri.
//
#pragma once
#include "../Engine.h"


namespace Engine
{
	enum class LogType : WORD
	{
		Info = FOREGROUND_BLUE,
		Warning = FOREGROUND_RED | FOREGROUND_GREEN,
		Error = FOREGROUND_RED
	};

	class ENGINE_API Logger
	{
	private:
		HANDLE m_ConsoleHandle = NULL;

	public:
		Logger();
		~Logger();

		std::string Print(LogType MessageType, std::string Message, bool ForceNewline = false);
		void Clear();
	};
}