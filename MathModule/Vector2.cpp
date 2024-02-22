#include "MathHeaders.h"

const Vector2 Vector2::UnitX(1.f, 0.f);
const Vector2 Vector2::UnitY(0.f, 1.f);
const Vector2 Vector2::Zero(0.f, 0.f);
const Vector2 Vector2::One(1.f, 1.f);


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