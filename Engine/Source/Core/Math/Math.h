// Written by syri.
//
#pragma once


namespace Engine
{
	struct Vector2
	{
		float X;
		float Y;

		Vector2(float InX, float InY)
			: X(InX), Y(InY)
		{}
	};

	struct Vector3
	{
		float X;
		float Y;
		float Z;

		Vector3(float InX, float InY, float InZ)
			: X(InX), Y(InY), Z(InZ)
		{}
	};

	struct Vector4
	{
		float W;
		float X;
		float Y;
		float Z;

		Vector4(float InW, float InX, float InY, float InZ)
			: W(InW), X(InX), Y(InY), Z(InZ)
		{}
	};

	struct Rotator
	{
		float Pitch;
		float Yaw;
		float Roll;

		Rotator(float InPitch, float InYaw, float InRoll)
			: Pitch(InPitch), Yaw(InYaw), Roll(InRoll)
		{}
	};

	struct Transform
	{
		Vector3 Location;
		Rotator Rotation;
		Vector3 Scale;

		Transform(Vector3 InLocation, Rotator InRotation, Vector3 InScale)
			: Location(InLocation), Rotation(InRotation), Scale(InScale)
		{}
	};
}