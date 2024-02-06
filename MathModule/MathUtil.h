#pragma once

struct MathUtil{
	static constexpr float PI = { 3.14159265358979323846f };
	static constexpr float TwoPI = { 2.f * PI };
	static constexpr float HalfPI = { 1.57079632679f };
	static constexpr float InvPI = { 0.31830988618f };
	static constexpr char InvalidHashName[] = "!@CK_INVALIDHASH#$";
	static const std::size_t InvalidHash;

	static constexpr int TruncToInt(float InFloat)
	{
		return (int)InFloat;
	}

	static constexpr int RountToInt(float InFloat)
	{
		return TruncToInt(roundf(InFloat));
	}

	static constexpr int FloorToInt(float InFloat)
	{
		return TruncToInt(floorf(InFloat));
	}
};