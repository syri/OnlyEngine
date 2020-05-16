// Written by syri.
//
#pragma once
#include "../../Engine.h"


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

		template <typename... Arguments>
		static std::string Print(LogType InLogType, bool InForceEndline, std::string InMessage, Arguments&&... InArguments)
		{
			std::string Message = fmt::format(InMessage, InArguments...);

			// Output message type.
			if (InLogType == LogType::Info) fmt::print(fmt::fg(fmt::color::deep_sky_blue), "[INFO] ");
			else if (InLogType == LogType::Warning) fmt::print(fmt::fg(fmt::color::yellow), "[WARNING] ");
			else if (InLogType == LogType::Error) fmt::print(fmt::fg(fmt::color::red), "[ERROR] ");

			else if (InLogType == LogType::Success) fmt::print(fmt::fg(fmt::color::lime_green), "[SUCCESS] ");
			else if (InLogType == LogType::Failure) fmt::print(fmt::fg(fmt::color::red), "[FAILURE] ");

			// Output message.
			fmt::print(fmt::fg(fmt::color::white), Message);

			if (InForceEndline) std::cout << std::endl;

			return Message;
		}

	};
}