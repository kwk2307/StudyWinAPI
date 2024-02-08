#pragma once

struct Vector4 {
public:
	constexpr Vector4() = default;
	explicit constexpr Vector4(int InX, int InY, int InZ, int InW) : X((float)InX), Y((float)InY), Z((float)InZ), W((float)InW) { };
	explicit constexpr Vector4(float InX, float InY, float InZ, float InW) : X(InX), Y(InY), Z(InZ), W(InW) { };

	// Á¤Àû¸â¹öº¯¼ö 
	static const Vector4 UnitX;
	static const Vector4 UnitY;
	static const Vector4 UnitZ;
	static const Vector4 UnitW;
	static const Vector4 One;
	static const Vector4 Zero;
	static constexpr BYTE Dimension = 4;

	// ¸â¹öº¯¼ö
	union
	{
		struct
		{
			float X, Y, Z, W;
		};

		std::array<float, Dimension> Scalars = { 0.f, 0.f, 0.f,0.f };
	};
};