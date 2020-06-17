// Written by syri.
//
#pragma once


namespace Engine
{
	struct Vector2
	{
		float X;
		float Y;

		Vector2(const float InX, const float InY)
			: X(InX), Y(InY)
		{}

	};

	struct Vector3
	{
		float X;
		float Y;
		float Z;

		Vector3(const float InX, const float InY, const float InZ)
			: X(InX), Y(InY), Z(InZ)
		{}

	};

	struct Vector4
	{
		float W;
		float X;
		float Y;
		float Z;

		Vector4(const float InW, const float InX, const float InY, const float InZ)
			: W(InW), X(InX), Y(InY), Z(InZ)
		{}

	};

	struct Rotator
	{
		float Pitch;
		float Yaw;
		float Roll;

		Rotator(const float InPitch, const float InYaw, const float InRoll)
			: Pitch(InPitch), Yaw(InYaw), Roll(InRoll)
		{}

	};

	struct Transform
	{
		Vector3 Location;
		Rotator Rotation;
		Vector3 Scale;

		Transform(const Vector3 InLocation, const Rotator InRotation, const Vector3 InScale)
			: Location(InLocation), Rotation(InRotation), Scale(InScale)
		{}

	};
}