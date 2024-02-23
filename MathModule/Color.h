#pragma once

struct Color {
public:
	constexpr Color(): R(0),G(0),B(0),A(0){}
	explicit constexpr Color(BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255) : R(InR), G(InG), B(InB), A(InA) { }
	explicit constexpr Color(UINT32 InColor) : ColorValue(InColor) { }

	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Blue;
	static const Color Green;

public:
	union
	{
		struct
		{
			BYTE B, G, R, A;
		};

		UINT32 ColorValue;
	};
};
