// Written by syri.
//
#pragma once
#include "../../Engine.h"
#include "../Math/Colour.h"


namespace Engine
{
	struct PRAE_API WindowDescriptor
	{
		std::wstring WindowTitle;

		int X;
		int Y;
		unsigned int Width;
		unsigned int Height;
		bool Fullscreen;

		HWND WindowHandle;
		FloatColour ClearColour;

		WindowDescriptor(std::wstring InWindowTitle, int InX, int InY, unsigned int InWidth, unsigned int InHeight, bool InFullscreen) :
			WindowTitle(InWindowTitle), X(InX), Y(InY), Width(InWidth), Height(InHeight), Fullscreen(InFullscreen), WindowHandle(0),
			ClearColour(FloatColour(0.f, 0.f, 0.f, 0.f))
		{}

		WindowDescriptor(std::wstring InWindowTitle, unsigned int InWidth, unsigned int InHeight, bool InFullscreen) :
			WindowTitle(InWindowTitle), X(0), Y(0), Width(InWidth), Height(InHeight), Fullscreen(InFullscreen), WindowHandle(0),
			ClearColour(FloatColour(0.f, 0.f, 0.f, 0.f))
		{}
	};
}
