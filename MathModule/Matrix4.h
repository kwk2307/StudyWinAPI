#pragma once
struct Matrix4 {
public:
	constexpr Matrix4() = default;
	explicit constexpr Matrix4(const Vector4& InCol0, const Vector4& InCol1, const Vector4& InCol2, const Vector4& InCol3) { Cols = { InCol0, InCol1, InCol2, InCol3 }; }

	// 연산자 
	 __forceinline const Vector4& operator[](BYTE InIndex) const;
	 __forceinline Vector4& operator[](BYTE InIndex);
	 __forceinline constexpr Matrix4 operator*(float InScalar) const;
	 __forceinline constexpr Matrix4 operator*(const Matrix4& InMatrix) const;
	 __forceinline constexpr Vector4 operator*(const Vector4& InVector) const;
	 __forceinline friend Vector4 operator*=(Vector4& InVector, const Matrix4& InMatrix)
	{
		InVector = InMatrix * InVector;
		return InVector;
	}
	 __forceinline constexpr Vector3 operator*(const Vector3& InVector) const;
	 __forceinline friend Vector3 operator*=(Vector3& InVector, const Matrix4& InMatrix)
	{
		InVector = InMatrix * InVector;
		return InVector;
	}

	// 멤버함수 
	Matrix3 ToMatrix3() const;
	void SetIdentity();
	__forceinline constexpr Matrix4 Transpose() const;

	// 정적멤버변수 
	static const Matrix4 Identity;
	static constexpr BYTE Rank = 4;

	std::array<Vector4, Rank> Cols = { Vector4::UnitX, Vector4::UnitY, Vector4::UnitZ, Vector4::UnitW };
};

__forceinline const Vector4& Matrix4::operator[](BYTE InIndex) const
{
	assert(InIndex < Rank);
	return Cols[InIndex];
}

__forceinline Vector4& Matrix4::operator[](BYTE InIndex)
{
	assert(InIndex < Rank);
	return Cols[InIndex];
}

__forceinline constexpr Matrix4 Matrix4::operator*(float InScalar) const
{
	return Matrix4(
		Cols[0] * InScalar,
		Cols[1] * InScalar,
		Cols[2] * InScalar,
		Cols[3] * InScalar
	);
}

__forceinline constexpr Matrix4 Matrix4::operator*(const Matrix4& InMatrix) const
{
	Matrix4 transposedMatrix = Transpose();
	return Matrix4(
		Vector4(transposedMatrix[0].Dot(InMatrix[0]), transposedMatrix[1].Dot(InMatrix[0]), transposedMatrix[2].Dot(InMatrix[0]), transposedMatrix[3].Dot(InMatrix[0])),
		Vector4(transposedMatrix[0].Dot(InMatrix[1]), transposedMatrix[1].Dot(InMatrix[1]), transposedMatrix[2].Dot(InMatrix[1]), transposedMatrix[3].Dot(InMatrix[1])),
		Vector4(transposedMatrix[0].Dot(InMatrix[2]), transposedMatrix[1].Dot(InMatrix[2]), transposedMatrix[2].Dot(InMatrix[2]), transposedMatrix[3].Dot(InMatrix[2])),
		Vector4(transposedMatrix[0].Dot(InMatrix[3]), transposedMatrix[1].Dot(InMatrix[3]), transposedMatrix[2].Dot(InMatrix[3]), transposedMatrix[3].Dot(InMatrix[3]))
	);
}

__forceinline constexpr Vector4 Matrix4::operator*(const Vector4& InVector) const
{
	Matrix4 transposedMatrix = Transpose();
	return Vector4(
		transposedMatrix[0].Dot(InVector),
		transposedMatrix[1].Dot(InVector),
		transposedMatrix[2].Dot(InVector),
		transposedMatrix[3].Dot(InVector)
	);
}

__forceinline constexpr Vector3 Matrix4::operator*(const Vector3& InVector) const
{
	Vector4 v4(InVector);
	Vector4 result = *this * v4;

	return Vector3(result.X, result.Y, result.Z);
}

__forceinline Matrix3 Matrix4::ToMatrix3() const
{
	return Matrix3(Cols[0].ToVector3(), Cols[1].ToVector3(), Cols[2].ToVector3());
}

__forceinline void Matrix4::SetIdentity()
{
	*this = Matrix4::Identity;
}

__forceinline constexpr Matrix4 Matrix4::Transpose() const
{
	return Matrix4(
		Vector4(Cols[0].X, Cols[1].X, Cols[2].X, Cols[3].X),
		Vector4(Cols[0].Y, Cols[1].Y, Cols[2].Y, Cols[3].Y),
		Vector4(Cols[0].Z, Cols[1].Z, Cols[2].Z, Cols[3].Z),
		Vector4(Cols[0].W, Cols[1].W, Cols[2].W, Cols[3].W)
	);
}
