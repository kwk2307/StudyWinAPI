#pragma once
struct Matrix4 {
public:
	constexpr Matrix4() = default;
	explicit constexpr Matrix4(const Vector4& InCol0, const Vector4& InCol1, const Vector4& InCol2, const Vector4& InCol3) { Cols = { InCol0, InCol1, InCol2, InCol3 }; }


	// 연산자 
	____forceinline const Vector4& operator[](BYTE InIndex) const;
	____forceinline Vector4& operator[](BYTE InIndex);
	____forceinline constexpr Matrix4 operator*(float InScalar) const;
	____forceinline constexpr Matrix4 operator*(const Matrix4& InMatrix) const;
	____forceinline constexpr Vector4 operator*(const Vector4& InVector) const;
	____forceinline friend Vector4 operator*=(Vector4& InVector, const Matrix4& InMatrix)
	{
		InVector = InMatrix * InVector;
		return InVector;
	}
	____forceinline constexpr Vector3 operator*(const Vector3& InVector) const;
	____forceinline friend Vector3 operator*=(Vector3& InVector, const Matrix4& InMatrix)
	{
		InVector = InMatrix * InVector;
		return InVector;
	}

	// 멤버함수 
	____forceinline Matrix4 ToMatrix3x3() const;
	____forceinline void SetIdentity();
	____forceinline constexpr Matrix4 Transpose() const;

	// 정적멤버변수 
	static const Matrix4 Identity;
	static constexpr BYTE Rank = 4;

	std::array<Vector4, Rank> Cols = { Vector4::UnitX, Vector4::UnitY, Vector4::UnitZ, Vector4::UnitW };
};

