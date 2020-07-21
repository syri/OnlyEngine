// Written by syri.
//
#pragma once
#include <Engine.h>


namespace Engine
{
	enum class UMA_API ELogType : unsigned int
	{
		Info = 1,
		Warning,
		Error,

		Success,
		Failure
	};

	class UMA_API CLogger
	{
	public:
		static bool s_Initialised;

	public:
		static void Setup();
		static void Clear();

		template <typename... Arguments>
		static void Print(const ELogType InLogType, const wchar_t* InMessage, const bool InForceEndline = true, Arguments&&... InArguments)
		{
			if (!s_Initialised) Setup();

			PrintLogType(InLogType);

			// Output message.
			std::wcout << InMessage;

			if (InForceEndline) std::wcout << std::endl;
		}

		static void PrintLogType(const ELogType InLogType)
		{
			// Output message type.
			switch (InLogType)
			{
			case ELogType::Warning:
				std::wcout << TEXT("\x1B[38;2;255;255;0m") << TEXT("[WARNING] ") << "\033[0m";

				break;
			case ELogType::Error:
				std::wcout << TEXT("\x1B[38;2;255;0;0m") << TEXT("[ERROR] ") << "\033[0m";

				break;
			case ELogType::Success:
				std::wcout << TEXT("\x1B[38;2;50;205;50m") << TEXT("[SUCCESS] ") << "\033[0m";

				break;
			case ELogType::Failure:
				std::wcout << TEXT("\x1B[38;2;255;0;0m") << TEXT("[FAILURE] ") << "\033[0m";

				break;
			default:
				std::wcout << TEXT("\x1B[38;2;0;191;255m") << TEXT("[INFO] ") << "\033[0m";

				break;
			}
		}

	};
}
