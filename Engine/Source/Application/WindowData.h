// Written by syri.
//
#pragma once
#include <API.h>
#include <Math/Colour.h>


namespace Engine
{
	enum class UMA_API EWindowMode : uint32_t
	{
		Windowed = 1,
		WindowedBorderless,
		Fullscreen
	};

	struct UMA_API SWindowDescriptor
	{
		const wchar_t *Title;

		int32_t X;
		int32_t Y;
		uint32_t Width;
		uint32_t Height;
		EWindowMode Mode;

		HWND Handle;
		SColour ClearColour;

		SWindowDescriptor(const wchar_t* InTitle, const int32_t InX, const int32_t InY, const uint32_t InWidth, const uint32_t InHeight, const EWindowMode InMode)
			: Title(InTitle), X(InX), Y(InY), Width(InWidth), Height(InHeight), Mode(InMode), Handle(nullptr)
			, ClearColour(SColour(0.f, 0.f, 0.f, 0.f))
		{}

		SWindowDescriptor(const wchar_t* InTitle, const uint32_t InWidth, const uint32_t InHeight, const EWindowMode InMode)
			: Title(InTitle), X(0), Y(0), Width(InWidth), Height(InHeight), Mode(InMode), Handle(nullptr)
			, ClearColour(SColour(0.f, 0.f, 0.f, 0.f))
		{}

	};
}
