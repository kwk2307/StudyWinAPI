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

constexpr float Vector2::operator[](BYTE InIndex) const
{
	assert(InIndex < Dimension);
	return Scalars[InIndex];
}

constexpr float& Vector2::operator[](BYTE InIndex)
{
	assert(InIndex < Dimension);
	return Scalars[InIndex];
}

constexpr Vector2 Vector2::operator-() const
{
	return Vector2(-X, -Y);
}

constexpr Vector2 Vector2::operator*(float InScalar) const
{
	return Vector2(X * InScalar, Y * InScalar);
}

constexpr Vector2 Vector2::operator/(float InScalar) const
{
	return Vector2(X / InScalar, Y / InScalar);
}

constexpr Vector2 Vector2::operator+(const Vector2& InVector) const
{
	return Vector2(X + InVector.X, Y + InVector.Y);
}

constexpr Vector2 Vector2::operator-(const Vector2& InVector) const
{
	return Vector2(X - InVector.X, Y - InVector.Y);
}

constexpr Vector2 Vector2::operator*(const Vector2& InVector) const
{
	return Vector2(X * InVector.X, Y * InVector.Y);
}

constexpr Vector2& Vector2::operator*=(float InScale)
{
	X *= InScale;
	Y *= InScale;
	return *this;
}

constexpr Vector2& Vector2::operator/=(float InScale)
{
	X /= InScale;
	Y /= InScale;
	return *this;
}

constexpr Vector2& Vector2::operator+=(const Vector2& InVector)
{
	X += InVector.X;
	Y += InVector.Y;
	return *this;
}

constexpr Vector2& Vector2::operator-=(const Vector2& InVector)
{
	X -= InVector.X;
	Y -= InVector.Y;
	return *this;
}

constexpr float Vector2::Dot(const Vector2& InVector) const
{
	return X * InVector.X + Y * InVector.Y;
}