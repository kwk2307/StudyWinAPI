#pragma once

struct Vector2 {
public:
	constexpr Vector2() = default;
	explicit constexpr Vector2(int InX, int InY) : X((float)InX), Y((float)InY) { };
	explicit constexpr Vector2(float InX, float InY) : X(InX), Y(InY) { };

	// ����������� 
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 One;
	static const Vector2 Zero;
	static constexpr BYTE Dimension = 2;

	// �������
	union
	{
		struct
		{
			float X, Y;
		};

		std::array<float, Dimension> Scalars = { 0.f, 0.f };
	};
};