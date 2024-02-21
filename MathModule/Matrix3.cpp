#include "MathHeaders.h"

const Vector3& Matrix3::operator[](BYTE InIndex) const
{
	assert(InIndex < Rank);
	return Cols[InIndex];
}

Vector3& Matrix3::operator[](BYTE InIndex)
{
	assert(InIndex < Rank);
	return Cols[InIndex];
}

Matrix3 Matrix3::operator*(float InScalar) const
{
	return Matrix3(
		Cols[0] * InScalar,
		Cols[1] * InScalar,
		Cols[2] * InScalar
	);
}

Matrix3 Matrix3::operator*(const Matrix3& InMatrix) const
{
	Matrix3 transposedMatrix = Transpose();
	return Matrix3(
		Vector3(transposedMatrix[0].Dot(InMatrix[0]), transposedMatrix[1].Dot(InMatrix[0]), transposedMatrix[2].Dot(InMatrix[0])),
		Vector3(transposedMatrix[0].Dot(InMatrix[1]), transposedMatrix[1].Dot(InMatrix[1]), transposedMatrix[2].Dot(InMatrix[1])),
		Vector3(transposedMatrix[0].Dot(InMatrix[2]), transposedMatrix[1].Dot(InMatrix[2]), transposedMatrix[2].Dot(InMatrix[2]))
	);
}

Vector3 Matrix3::operator*(const Vector3& InVector) const
{
	Matrix3 transposedMatrix = Transpose();
	return Vector3(
		transposedMatrix[0].Dot(InVector),
		transposedMatrix[1].Dot(InVector),
		transposedMatrix[2].Dot(InVector)
	);
}

Vector2 Matrix3::operator*(const Vector2& InVector) const
{
	Vector3 v3(InVector);
	v3 *= *this;

	return v3.ToVector2();
}

void Matrix3::SetIdentity()
{
	*this = Matrix3::Identity;
}

Matrix3 Matrix3::Transpose() const
{
	return Matrix3(
		Vector3(Cols[0].X, Cols[1].X, Cols[2].X),
		Vector3(Cols[0].Y, Cols[1].Y, Cols[2].Y),
		Vector3(Cols[0].Z, Cols[1].Z, Cols[2].Z)
	);
}
