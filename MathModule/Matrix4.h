#pragma once
struct Matrix4 {
public:
	constexpr Matrix4() = default;
	explicit constexpr Matrix4(const Vector4& InCol0, const Vector4& InCol1, const Vector4& InCol2, const Vector4& InCol3) { Cols = { InCol0, InCol1, InCol2, InCol3 }; }

	// 연산자 
	 const Vector4& operator[](BYTE InIndex) const;
	 Vector4& operator[](BYTE InIndex);
	 constexpr Matrix4 operator*(float InScalar) const;
	 constexpr Matrix4 operator*(const Matrix4& InMatrix) const;
	 constexpr Vector4 operator*(const Vector4& InVector) const;
	 friend Vector4 operator*=(Vector4& InVector, const Matrix4& InMatrix)
	{
		InVector = InMatrix * InVector;
		return InVector;
	}
	 constexpr Vector3 operator*(const Vector3& InVector) const;
	 friend Vector3 operator*=(Vector3& InVector, const Matrix4& InMatrix)
	{
		InVector = InMatrix * InVector;
		return InVector;
	}

	// 멤버함수 
	Matrix3 ToMatrix3() const;
	 void SetIdentity();
	 constexpr Matrix4 Transpose() const;

	// 정적멤버변수 
	static const Matrix4 Identity;
	static constexpr BYTE Rank = 4;

	std::array<Vector4, Rank> Cols = { Vector4::UnitX, Vector4::UnitY, Vector4::UnitZ, Vector4::UnitW };
};

