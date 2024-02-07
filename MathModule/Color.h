#pragma once

struct Color {
public:
	constexpr Color(): R(0),G(0),B(0),A(0){}
	explicit constexpr Color(BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255) : B(InB), G(InG), R(InR), A(InA) { }
	explicit constexpr Color(UINT32 InColor) : ColorValue(InColor) { }

public:
	union
	{
		struct
		{
			BYTE R, G, B, A;
		};

		UINT32 ColorValue;
	};
};