#pragma once

struct Vector2 {
public:
	constexpr Vector2() = default;
	explicit constexpr Vector2(int InX, int InY) : X((float)InX), Y((float)InY) { };
	explicit constexpr Vector2(float InX, float InY) : X(InX), Y(InY) { };

	// 연산자 
	__forceinline constexpr float operator[](BYTE InIndex) const;
	__forceinline constexpr float& operator[](BYTE InIndex);
	__forceinline constexpr Vector2 operator-() const;
	__forceinline constexpr Vector2 operator*(float InScalar) const;
	__forceinline constexpr Vector2 operator/(float InScalar) const;
	__forceinline constexpr Vector2 operator*(const Vector2& InVector) const;
	__forceinline constexpr Vector2 operator+(const Vector2& InVector) const;
	__forceinline constexpr Vector2 operator-(const Vector2& InVector) const;
	__forceinline constexpr Vector2& operator*=(float InScale);
	__forceinline constexpr Vector2& operator/=(float InScale);
	__forceinline constexpr Vector2& operator+=(const Vector2& InVector);
	__forceinline constexpr Vector2& operator-=(const Vector2& InVector);

	// 멤버함수 
	__forceinline float Size() const;
	__forceinline constexpr float SizeSquared() const;
	void Normalize();
	[[nodiscard]] Vector2 GetNormalize() const;
	__forceinline constexpr bool EqualsInTolerance(const Vector2& InVector, float InTolerance = SMALL_NUMBER) const;
	__forceinline constexpr float Max() const;
	__forceinline constexpr float Dot(const Vector2& InVector) const;

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

__forceinline constexpr float Vector2::operator[](BYTE InIndex) const
{
	assert(InIndex < Dimension);
	return Scalars[InIndex];
}

__forceinline constexpr float& Vector2::operator[](BYTE InIndex)
{
	assert(InIndex < Dimension);
	return Scalars[InIndex];
}

__forceinline constexpr Vector2 Vector2::operator-() const
{
	return Vector2(-X, -Y);
}

__forceinline constexpr Vector2 Vector2::operator*(float InScalar) const
{
	return Vector2(X * InScalar, Y * InScalar);
}

__forceinline constexpr Vector2 Vector2::operator/(float InScalar) const
{
	return Vector2(X / InScalar, Y / InScalar);
}

__forceinline constexpr Vector2 Vector2::operator+(const Vector2& InVector) const
{
	return Vector2(X + InVector.X, Y + InVector.Y);
}

__forceinline constexpr Vector2 Vector2::operator-(const Vector2& InVector) const
{
	return Vector2(X - InVector.X, Y - InVector.Y);
}

__forceinline constexpr Vector2 Vector2::operator*(const Vector2& InVector) const
{
	return Vector2(X * InVector.X, Y * InVector.Y);
}

__forceinline constexpr Vector2& Vector2::operator*=(float InScale)
{
	X *= InScale;
	Y *= InScale;
	return *this;
}

__forceinline constexpr Vector2& Vector2::operator/=(float InScale)
{
	X /= InScale;
	Y /= InScale;
	return *this;
}

__forceinline constexpr Vector2& Vector2::operator+=(const Vector2& InVector)
{
	X += InVector.X;
	Y += InVector.Y;
	return *this;
}

__forceinline constexpr Vector2& Vector2::operator-=(const Vector2& InVector)
{
	X -= InVector.X;
	Y -= InVector.Y;
	return *this;
}

__forceinline float Vector2::Size() const
{
	return sqrtf(SizeSquared());
}

__forceinline constexpr float Vector2::SizeSquared() const
{
	return X * X + Y * Y;
}

__forceinline void Vector2::Normalize()
{
	*this = GetNormalize();
}

__forceinline constexpr bool Vector2::EqualsInTolerance(const Vector2& InVector, float InTolerance) const
{
	return (MathUtil::Abs(this->X - InVector.X) <= InTolerance) &&
		(MathUtil::Abs(this->Y - InVector.Y) < InTolerance);
}

__forceinline constexpr float Vector2::Max() const
{
	return MathUtil::Max(X, Y);
}

__forceinline constexpr float Vector2::Dot(const Vector2& InVector) const
{
	return X * InVector.X + Y * InVector.Y;
}