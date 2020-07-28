// Written by syri.
//
#pragma once
#include <API.h>
#include <Math/Colour.h>


namespace Engine
{
	enum class UMA_API EWindowMode : unsigned int
	{
		Windowed = 1,
		WindowedBorderless,
		Fullscreen
	};

	struct UMA_API SWindowDescriptor
	{
		const wchar_t *Title;

		int X;
		int Y;
		unsigned int Width;
		unsigned int Height;
		EWindowMode Mode;

		HWND Handle;
		SColour ClearColour;

		SWindowDescriptor(const wchar_t* InTitle, const int InX, const int InY, const unsigned int InWidth, const unsigned int InHeight, const EWindowMode InMode)
			: Title(InTitle), X(InX), Y(InY), Width(InWidth), Height(InHeight), Mode(InMode), Handle(nullptr)
			, ClearColour(SColour(0.f, 0.f, 0.f, 0.f))
		{}

		SWindowDescriptor(const wchar_t* InTitle, const unsigned int InWidth, const unsigned int InHeight, const EWindowMode InMode)
			: Title(InTitle), X(0), Y(0), Width(InWidth), Height(InHeight), Mode(InMode), Handle(nullptr)
			, ClearColour(SColour(0.f, 0.f, 0.f, 0.f))
		{}

	};
}
