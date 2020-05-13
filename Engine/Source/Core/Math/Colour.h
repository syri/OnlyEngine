// Written by syri.
//
#pragma once


namespace Engine
{
	struct RGBA8Colour
	{
		int Red;
		int Green;
		int Blue;
		int Alpha;

		RGBA8Colour(int InRed, int InGreen, int InBlue, int InAlpha)
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

		FloatColour(float InRed, float InGreen, float InBlue, float InAlpha)
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