#pragma once
struct LinearColor
{
public:
	__forceinline constexpr LinearColor() = default;
	__forceinline explicit constexpr LinearColor(float InR, float InG, float InB, float InA = 1.f) : R(InR), G(InG), B(InB), A(InA) {}
	__forceinline explicit constexpr LinearColor(const Color32& InColor32)
	{
		R = float(InColor32.R) * OneOver255;
		G = float(InColor32.G) * OneOver255;
		B = float(InColor32.B) * OneOver255;
		A = float(InColor32.A) * OneOver255;
	}

	static constexpr float OneOver255 = { 1.f / 255.f };
public:
	float R = 0.f;
	float G = 0.f;
	float B = 0.f;
	float A = 0.f;

};