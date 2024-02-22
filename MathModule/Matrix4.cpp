#include "MathHeaders.h"

const Matrix4 Matrix4::Identity(Vector4(1.f, 0.f, 0.f, 0.f), Vector4(0.f, 1.f, 0.f, 0.f), Vector4(0.f, 0.f, 1.f, 0.f), Vector4(0.f, 0.f, 0.f, 1.f));

const Vector4& Matrix4::operator[](BYTE InIndex) const
{
	assert(InIndex < Rank);
	return Cols[InIndex];
}

Vector4& Matrix4::operator[](BYTE InIndex)
{
	assert(InIndex < Rank);
	return Cols[InIndex];
}

constexpr Matrix4 Matrix4::operator*(float InScalar) const
{
	return Matrix4(
		Cols[0] * InScalar,
		Cols[1] * InScalar,
		Cols[2] * InScalar,
		Cols[3] * InScalar
	);
}

constexpr Matrix4 Matrix4::operator*(const Matrix4& InMatrix) const
{
	Matrix4 transposedMatrix = Transpose();
	return Matrix4(
		Vector4(transposedMatrix[0].Dot(InMatrix[0]), transposedMatrix[1].Dot(InMatrix[0]), transposedMatrix[2].Dot(InMatrix[0]), transposedMatrix[3].Dot(InMatrix[0])),
		Vector4(transposedMatrix[0].Dot(InMatrix[1]), transposedMatrix[1].Dot(InMatrix[1]), transposedMatrix[2].Dot(InMatrix[1]), transposedMatrix[3].Dot(InMatrix[1])),
		Vector4(transposedMatrix[0].Dot(InMatrix[2]), transposedMatrix[1].Dot(InMatrix[2]), transposedMatrix[2].Dot(InMatrix[2]), transposedMatrix[3].Dot(InMatrix[2])),
		Vector4(transposedMatrix[0].Dot(InMatrix[3]), transposedMatrix[1].Dot(InMatrix[3]), transposedMatrix[2].Dot(InMatrix[3]), transposedMatrix[3].Dot(InMatrix[3]))
	);
}

constexpr Vector4 Matrix4::operator*(const Vector4& InVector) const
{
	Matrix4 transposedMatrix = Transpose();
	return Vector4(
		transposedMatrix[0].Dot(InVector),
		transposedMatrix[1].Dot(InVector),
		transposedMatrix[2].Dot(InVector),
		transposedMatrix[3].Dot(InVector)
	);
}

constexpr Vector3 Matrix4::operator*(const Vector3& InVector) const
{
	Vector4 v4(InVector);
	Vector4 result = *this * v4;

	return Vector3(result.X, result.Y, result.Z);
}

Matrix3 Matrix4::ToMatrix3() const
{
	return Matrix3(Cols[0].ToVector3(), Cols[1].ToVector3(), Cols[2].ToVector3());
}

void Matrix4::SetIdentity()
{
	*this = Matrix4::Identity;
}

constexpr Matrix4 Matrix4::Transpose() const
{
	return Matrix4(
		Vector4(Cols[0].X, Cols[1].X, Cols[2].X, Cols[3].X),
		Vector4(Cols[0].Y, Cols[1].Y, Cols[2].Y, Cols[3].Y),
		Vector4(Cols[0].Z, Cols[1].Z, Cols[2].Z, Cols[3].Z),
		Vector4(Cols[0].W, Cols[1].W, Cols[2].W, Cols[3].W)
	);
}
