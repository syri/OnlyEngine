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
		static std::string Print(LogType InLogType, std::string Message, bool ForceEndline = false);
		static void Clear();

	};
}