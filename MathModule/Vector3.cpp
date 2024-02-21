#include "MathHeaders.h"

const Vector3 Vector3::UnitX(1.f, 0.f, 0.f);
const Vector3 Vector3::UnitY(0.f, 1.f, 0.f);
const Vector3 Vector3::UnitZ(0.f, 0.f, 1.f);
const Vector3 Vector3::Zero(0.f, 0.f, 0.f);
const Vector3 Vector3::One(1.f, 1.f, 1.f);

constexpr float Vector3::operator[](BYTE InIndex) const
{
	assert(InIndex < Dimension);
	return Scalars[InIndex];
}

 constexpr float Vector3::operator[](BYTE InIndex) const
{
	assert(InIndex < Dimension);
	return Scalars[InIndex];
}

 constexpr float& Vector3::operator[](BYTE InIndex)
{
	assert(InIndex < Dimension);
	return Scalars[InIndex];
}

 constexpr Vector3 Vector3::operator-() const
{
	return Vector3(-X, -Y, -Z);
}

 constexpr Vector3 Vector3::operator*(float InScale) const
{
	return Vector3(X * InScale, Y * InScale, Z * InScale);
}

 constexpr Vector3 Vector3::operator/(float InScale) const
{
	return Vector3(X / InScale, Y / InScale, Z / InScale);
}

 constexpr Vector3 Vector3::operator*(const Vector3& InVector) const
{
	return Vector3(X * InVector.X, Y * InVector.Y, Z * InVector.Z);
}

 constexpr Vector3 Vector3::operator+(const Vector3& InVector) const
{
	return Vector3(X + InVector.X, Y + InVector.Y, Z + InVector.Z);
}

 constexpr Vector3 Vector3::operator-(const Vector3& InVector) const
{
	return Vector3(X - InVector.X, Y - InVector.Y, Z - InVector.Z);
}

 constexpr Vector3& Vector3::operator*=(float InScale)
{
	X *= InScale;
	Y *= InScale;
	Z *= InScale;
	return *this;
}

 constexpr Vector3& Vector3::operator/=(float InScale)
{
	X /= InScale;
	Y /= InScale;
	Z /= InScale;
	return *this;
}

 constexpr Vector3& Vector3::operator+=(const Vector3& InVector)
{
	X += InVector.X;
	Y += InVector.Y;
	Z += InVector.Z;
	return *this;
}

 constexpr Vector3& Vector3::operator-=(const Vector3& InVector)
{
	X -= InVector.X;
	Y -= InVector.Y;
	Z -= InVector.Z;
	return *this;
}

 constexpr Vector2 Vector3::ToVector2() const
 {
	 return Vector2(X, Y);
 }

 constexpr float Vector3::Dot(const Vector3& InVector) const
 {
	 return X * InVector.X + Y * InVector.Y + Z * InVector.Z;
 }
