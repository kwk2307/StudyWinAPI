#pragma once

struct Vector3 {
public:
	constexpr Vector3() = default;
	explicit constexpr Vector3(int InX, int InY, int InZ) : X((float)InX), Y((float)InY), Z((float)InZ) { };
	explicit constexpr Vector3(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) { };

	// Á¤Àû¸â¹öº¯¼ö 
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 One;
	static const Vector3 Zero;
	static constexpr BYTE Dimension = 3;

	// ¸â¹öº¯¼ö
	union
	{
		struct
		{
			float X, Y, Z;
		};

		std::array<float, Dimension> Scalars = { 0.f, 0.f, 0.f };
	};
};