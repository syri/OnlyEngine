// Written by syri.
//
#pragma once
#include "../../Engine.h"


namespace Engine
{
	enum class LogType : unsigned int
	{
		Info,
		Warning,
		Error,

		Success,
		Failure
	};

	class PRAE_API Logger
	{
	public:
		static void Setup();
		static std::string Print(LogType MessageType, std::string Message, bool ForceEndline = false);
		static void Clear();
	};
}