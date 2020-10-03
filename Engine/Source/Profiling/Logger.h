// Written by syri.
//
#pragma once
#include <API.h>
#include <typeinfo>

namespace Engine
{
	enum class UMA_API ELogType : uint32_t
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
		inline static bool s_bInitialised = false;

	public:
		static void Setup();
		static void Clear();

		static void Print(const ELogType InLogType, const wchar_t* InMessage)
		{
			if (!s_bInitialised) Setup();

			PrintLogType(InLogType);

			// Output message.
			std::wcout << InMessage;
		}

		template<typename... ArgumentTypes>
		static void Print(const ELogType InLogType, const wchar_t* InMessage, const std::vector<std::variant<ArgumentTypes...>>& InArguments)
		{
			std::wstring Message = InMessage;

			if (InArguments.size() > 0)
			{
				int32_t Index = 0;

				for (const auto& Argument : InArguments)
				{
					wchar_t Buffer[8];
					wsprintf(Buffer, TEXT("{%i}"), Index);

					size_t Location = 0;
					Location = Message.find(Buffer);

					std::visit([&](const auto& Value)
						{
							if (Location != std::wstring::npos)
							{
								Message = Message.replace(Location, 3, std::to_wstring(Value));
							}
						}
					, Argument);

					Index++;
				}
			}

			Print(InLogType, Message.c_str());
		}

		static void PrintLine(const ELogType InLogType, const wchar_t* InMessage)
		{
			Print(InLogType, InMessage);

			std::wcout << std::endl;
		}

		template<typename... ArgumentTypes>
		static void PrintLine(const ELogType InLogType, const wchar_t* InMessage, const std::vector<std::variant<ArgumentTypes...>>& InArguments)
		{
			Print(InLogType, InMessage, InArguments);

			std::wcout << std::endl;
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

namespace std
{
	_NODISCARD inline wstring to_wstring(wstring _Val) {
		return _Val;
	}
}
