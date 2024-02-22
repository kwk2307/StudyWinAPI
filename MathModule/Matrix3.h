#pragma once

struct Matrix3
{
public:
	// ������ 
	 constexpr Matrix3() = default;
	 explicit constexpr Matrix3(const Vector3& InCol0, const Vector3& InCol1, const Vector3& InCol2) { Cols = { InCol0, InCol1, InCol2 }; }

	// ������ 
	 const Vector3& operator[](BYTE InIndex) const;
	 Vector3& operator[](BYTE InIndex);

	 Matrix3 operator*(float InScalar) const;
	 Matrix3 operator*(const Matrix3& InMatrix) const;
	 Vector3 operator*(const Vector3& InVector) const;
	 friend Vector3 operator*=(Vector3& InVector, const Matrix3& InMatrix)
	{
		InVector = InMatrix * InVector;
		return InVector;
	}
	 Vector2 operator*(const Vector2& InVector) const;
	 friend Vector2 operator*=(Vector2& InVector, const Matrix3& InMatrix)
	{
		InVector = InMatrix * InVector;
		return InVector;
	}

	// ����Լ� 
	 void SetIdentity();
	 Matrix3 Transpose() const;

	// ����������� 
	static const Matrix3 Identity;
	static constexpr BYTE Rank = 3;

	// ������� 
	std::array<Vector3, Rank> Cols = { Vector3::UnitX, Vector3::UnitY, Vector3::UnitZ };
};