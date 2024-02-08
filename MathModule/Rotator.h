#pragma once

struct Rotator
{
public:
	constexpr Rotator() = default;
	constexpr Rotator(float InYaw, float InRoll, float InPitch) : Yaw(InYaw), Roll(InRoll), Pitch(InPitch) { }

public:
	float Yaw = 0.f;
	float Roll = 0.f;
	float Pitch = 0.f;
};
