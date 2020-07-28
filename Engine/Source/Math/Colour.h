// Written by syri.
//
#pragma once
#include <Engine.h>


namespace Engine
{
	enum class UMA_API EColourType : unsigned int
	{
		R8G8B8A8 = 1
	};

	struct UMA_API SColour
	{
		float Red;
		float Green;
		float Blue;
		float Alpha;

		SColour(const float InRed, const float InGreen, const float InBlue, const float InAlpha)
			: Red(InRed), Green(InGreen), Blue(InBlue), Alpha(InAlpha)
		{
			Clamp();
		}

		SColour(EColourType InColourType, int InRed, const int InGreen, const int InBlue, const int InAlpha)
		{
			switch (InColourType)
			{
			case EColourType::R8G8B8A8:
				Red = static_cast<float>(InRed) / 255;
				Green = static_cast<float>(InGreen) / 255;
				Blue = static_cast<float>(InBlue) / 255;
				Alpha = static_cast<float>(InAlpha) / 255;

				break;
			}

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