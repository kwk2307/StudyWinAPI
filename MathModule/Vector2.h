#pragma once

struct Vector2 {
public:
	constexpr Vector2() = default;
	explicit constexpr Vector2(int InX, int InY) : X((float)InX), Y((float)InY) { };
	explicit constexpr Vector2(float InX, float InY) : X(InX), Y(InY) { };

	// 연산자 
	constexpr float operator[](BYTE InIndex) const;
	constexpr float& operator[](BYTE InIndex);
	constexpr Vector2 operator-() const;
	constexpr Vector2 operator*(float InScalar) const;
	constexpr Vector2 operator/(float InScalar) const;
	constexpr Vector2 operator*(const Vector2& InVector) const;
	constexpr Vector2 operator+(const Vector2& InVector) const;
	constexpr Vector2 operator-(const Vector2& InVector) const;
	constexpr Vector2& operator*=(float InScale);
	constexpr Vector2& operator/=(float InScale);
	constexpr Vector2& operator+=(const Vector2& InVector);
	constexpr Vector2& operator-=(const Vector2& InVector);

	constexpr float Dot(const Vector2& InVector) const;

	// 정적멤버변수 
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 One;
	static const Vector2 Zero;
	static constexpr BYTE Dimension = 2;



	// 멤버변수
	union
	{
		struct
		{
			float X, Y;
		};

		std::array<float, Dimension> Scalars = { 0.f, 0.f };
	};
};