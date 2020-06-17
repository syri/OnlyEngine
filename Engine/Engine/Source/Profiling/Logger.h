// Written by syri.
//
#pragma once
#include <Engine.h>


namespace Engine
{
	enum class LogType : unsigned int
	{
		Info = 1,
		Warning,
		Error,

		Success,
		Failure
	};

	class PRAESEGMEN_API Logger
	{
	public:
		static void Setup();
		static void Clear();

		static void Print(const LogType InLogType, const bool InForceEndline, const wchar_t* InMessage)
		{
			PrintLogType(InLogType);

			// Output message.
			std::wcout << InMessage;

			if (InForceEndline) std::wcout << std::endl;
		}

		template <typename... Arguments>
		static void Print(const LogType InLogType, const bool InForceEndline, const wchar_t* InMessage, Arguments&&... InArguments)
		{
			Print(InLogType, InForceEndline, InMessage);
		}

		static void PrintLogType(const LogType InLogType)
		{
			// Output message type.
			switch (InLogType)
			{
			case LogType::Warning:
				std::wcout << TEXT("\x1B[38;2;255;255;0m") << TEXT("[WARNING] ") << "\033[0m";

				break;
			case LogType::Error:;
				std::wcout << TEXT("\x1B[38;2;255;0;0m") << TEXT("[ERROR] ") << "\033[0m";

				break;
			case LogType::Success:;
				std::wcout << TEXT("\x1B[38;2;50;205;50m") << TEXT("[SUCCESS] ") << "\033[0m";

				break;
			case LogType::Failure:;
				std::wcout << TEXT("\x1B[38;2;255;0;0m") << TEXT("[FAILURE] ") << "\033[0m";

				break;
			default:;
				std::wcout << TEXT("\x1B[38;2;0;191;255m") << TEXT("[INFO] ") << "\033[0m";

				break;
			}
		}

	};
}
