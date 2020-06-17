// Written by syri.
//
#pragma once
#include <Engine.h>
#include <Math/Colour.h>


namespace Engine
{
	struct WindowDescriptor
	{
		const wchar_t* WindowTitle;

		int X;
		int Y;
		unsigned int Width;
		unsigned int Height;
		bool Fullscreen;

		HWND WindowHandle;
		FloatColour ClearColour;

		WindowDescriptor(const wchar_t* InWindowTitle, const int InX, const int InY, const unsigned int InWidth, const unsigned int InHeight, const bool InFullscreen) :
			WindowTitle(InWindowTitle), X(InX), Y(InY), Width(InWidth), Height(InHeight), Fullscreen(InFullscreen), WindowHandle(0),
			ClearColour(FloatColour(0.f, 0.f, 0.f, 0.f))
		{}

		WindowDescriptor(const wchar_t* InWindowTitle, const unsigned int InWidth, const unsigned int InHeight, const bool InFullscreen) :
			WindowTitle(InWindowTitle), X(0), Y(0), Width(InWidth), Height(InHeight), Fullscreen(InFullscreen), WindowHandle(0),
			ClearColour(FloatColour(0.f, 0.f, 0.f, 0.f))
		{}

	};
}
