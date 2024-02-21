#pragma once

struct Matrix3
{
public:
	// 생성자 
	__forceinline constexpr Matrix3() = default;
	__forceinline explicit constexpr Matrix3(const Vector3& InCol0, const Vector3& InCol1, const Vector3& InCol2) { Cols = { InCol0, InCol1, InCol2 }; }

	// 연산자 
	__forceinline const Vector3& operator[](BYTE InIndex) const;
	__forceinline Vector3& operator[](BYTE InIndex);

	__forceinline Matrix3 operator*(float InScalar) const;
	__forceinline Matrix3 operator*(const Matrix3& InMatrix) const;
	__forceinline Vector3 operator*(const Vector3& InVector) const;
	__forceinline friend Vector3 operator*=(Vector3& InVector, const Matrix3& InMatrix)
	{
		InVector = InMatrix * InVector;
		return InVector;
	}
	__forceinline Vector2 operator*(const Vector2& InVector) const;
	__forceinline friend Vector2 operator*=(Vector2& InVector, const Matrix3& InMatrix)
	{
		InVector = InMatrix * InVector;
		return InVector;
	}

	// 멤버함수 
	__forceinline void SetIdentity();
	__forceinline Matrix3 Transpose() const;

	// 정적멤버변수 
	static const Matrix3 Identity;
	static constexpr BYTE Rank = 3;

	// 멤버변수 
	std::array<Vector3, Rank> Cols = { Vector3::UnitX, Vector3::UnitY, Vector3::UnitZ };
};