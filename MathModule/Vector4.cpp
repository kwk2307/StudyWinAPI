#include "MathHeaders.h"
const Vector4 Vector4::UnitX(1.f, 0.f, 0.f, 0.f);
const Vector4 Vector4::UnitY(0.f, 1.f, 0.f, 0.f);
const Vector4 Vector4::UnitZ(0.f, 0.f, 1.f, 0.f);
const Vector4 Vector4::UnitW(0.f, 0.f, 0.f, 1.f);
const Vector4 Vector4::Zero(0.f, 0.f, 0.f, 0.f);
const Vector4 Vector4::One(1.f, 1.f, 1.f, 1.f);

constexpr float Vector4::operator[](BYTE InIndex) const
{
	assert(InIndex < Dimension);
	return Scalars[InIndex];
}

constexpr float& Vector4::operator[](BYTE InIndex)
{
	assert(InIndex < Dimension);
	return Scalars[InIndex];
}

constexpr Vector4 Vector4::operator-() const
{
	return Vector4(-X, -Y, -Z, -W);
}

constexpr Vector4 Vector4::operator*(float InScale) const
{
	return Vector4(X * InScale, Y * InScale, Z * InScale, W * InScale);
}

constexpr Vector4 Vector4::operator/(float InScale) const
{
	return Vector4(X / InScale, Y / InScale, Z / InScale, W / InScale);
}

constexpr Vector4 Vector4::operator*(const Vector4& InVector) const
{
	return Vector4(X * InVector.X, Y * InVector.Y, Z * InVector.Z, W * InVector.W);
}

constexpr Vector4 Vector4::operator+(const Vector4& InVector) const
{
	return Vector4(X + InVector.X, Y + InVector.Y, Z + InVector.Z, W + InVector.W);
}

constexpr Vector4 Vector4::operator-(const Vector4& InVector) const
{
	return Vector4(X - InVector.X, Y - InVector.Y, Z - InVector.Z, W - InVector.W);
}

constexpr Vector4& Vector4::operator*=(float InScale)
{
	X *= InScale;
	Y *= InScale;
	Z *= InScale;
	W *= InScale;
	return *this;
}

constexpr Vector4& Vector4::operator/=(float InScale)
{
	X /= InScale;
	Y /= InScale;
	Z /= InScale;
	W /= InScale;
	return *this;
}

constexpr Vector4& Vector4::operator+=(const Vector4& InVector)
{
	X += InVector.X;
	Y += InVector.Y;
	Z += InVector.Z;
	W += InVector.W;
	return *this;
}

constexpr Vector4& Vector4::operator-=(const Vector4& InVector)
{
	X -= InVector.X;
	Y -= InVector.Y;
	Z -= InVector.Z;
	W -= InVector.W;
	return *this;
}

constexpr float Vector4::Dot(const Vector4& InVector) const
{
	return X * InVector.X + Y * InVector.Y + Z * InVector.Z + W * InVector.W;
}
