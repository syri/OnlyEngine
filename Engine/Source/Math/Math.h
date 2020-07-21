// Written by syri.
//
#pragma once


namespace Engine
{
	struct UMA_API SVector2
	{
		float X;
		float Y;

		SVector2(const float InX, const float InY)
			: X(InX), Y(InY)
		{}

	};

	struct UMA_API SVector3
	{
		float X;
		float Y;
		float Z;

		SVector3(const float InX, const float InY, const float InZ)
			: X(InX), Y(InY), Z(InZ)
		{}

	};

	struct UMA_API SVector4
	{
		float W;
		float X;
		float Y;
		float Z;

		SVector4(const float InW, const float InX, const float InY, const float InZ)
			: W(InW), X(InX), Y(InY), Z(InZ)
		{}

	};

	struct UMA_API SRotator
	{
		float Pitch;
		float Yaw;
		float Roll;

		SRotator(const float InPitch, const float InYaw, const float InRoll)
			: Pitch(InPitch), Yaw(InYaw), Roll(InRoll)
		{}

	};

	struct UMA_API STransform
	{
		SVector3 Location;
		SRotator Rotation;
		SVector3 Scale;

		STransform(const SVector3 InLocation, const SRotator InRotation, const SVector3 InScale)
			: Location(InLocation), Rotation(InRotation), Scale(InScale)
		{}

	};
}