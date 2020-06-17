// Written by syri.
//
#pragma once
#include <algorithm>


namespace Engine
{
	struct RGBA8Colour
	{
		int Red;
		int Green;
		int Blue;
		int Alpha;

		RGBA8Colour(const int InRed, const int InGreen, const int InBlue, int InAlpha)
			: Red(InRed), Green(InGreen), Blue(InBlue), Alpha(InAlpha)
		{
			Clamp();
		}

		void Clamp()
		{
			Red = std::clamp(Red, 0, 255);
			Green = std::clamp(Green, 0, 255);
			Blue = std::clamp(Blue, 0, 255);
			Alpha = std::clamp(Alpha, 0, 255);
		}

	};

	struct FloatColour
	{
		float Red;
		float Green;
		float Blue;
		float Alpha;

		FloatColour(const float InRed, const float InGreen, const float InBlue, const float InAlpha)
			: Red(InRed), Green(InGreen), Blue(InBlue), Alpha(InAlpha)
		{
			Clamp();
		}

		void Clamp()
		{
			Red = std::clamp(Red, 0.f, 1.f);
			Green = std::clamp(Green, 0.f, 1.f);
			Blue = std::clamp(Blue, 0.f, 1.f);
			Alpha = std::clamp(Alpha, 0.f, 1.f);
		}

	};
}
