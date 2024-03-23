#include "MathHeaders.h"

const Vector3 Vector3::UnitX(1.f, 0.f, 0.f);
const Vector3 Vector3::UnitY(0.f, 1.f, 0.f);
const Vector3 Vector3::UnitZ(0.f, 0.f, 1.f);
const Vector3 Vector3::Zero(0.f, 0.f, 0.f);
const Vector3 Vector3::One(1.f, 1.f, 1.f);

Vector3 Vector3::GetNormalize() const
{
	float squareSum = SizeSquared();
	if (squareSum == 1.f)
	{
		return *this;
	}
	else if (squareSum == 0.f)
	{
		return Vector3::Zero;
	}

	float invLength = MathUtil::InvSqrt(squareSum);
	return Vector3(X * invLength, Y * invLength, Z * invLength);
}