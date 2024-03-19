#pragma once

struct Vector3 {
public:
	constexpr Vector3() = default;
	explicit constexpr Vector3(const Vector2& InV, bool IsPoint = true) : X(InV.X), Y(InV.Y) { Z = IsPoint ? 1.f : 0.f; }
	explicit constexpr Vector3(int InX, int InY, int InZ) : X((float)InX), Y((float)InY), Z((float)InZ) { };
	explicit constexpr Vector3(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) { };

	// 연산자 
	__forceinline constexpr float operator[](BYTE InIndex) const;
	__forceinline constexpr float& operator[](BYTE InIndex);
	__forceinline constexpr Vector3 operator-() const;
	__forceinline constexpr Vector3 operator*(float InScale) const;
	__forceinline constexpr Vector3 operator/(float InScale) const;
	__forceinline constexpr Vector3 operator*(const Vector3& InVector) const;
	__forceinline constexpr Vector3 operator+(const Vector3& InVector) const;
	__forceinline constexpr Vector3 operator-(const Vector3& InVector) const;
	__forceinline constexpr Vector3& operator*=(float InScale);
	__forceinline constexpr Vector3& operator/=(float InScale);
	__forceinline constexpr Vector3& operator+=(const Vector3& InVector);
	__forceinline constexpr Vector3& operator-=(const Vector3& InVector);


	// 맴버 함수 
	__forceinline constexpr Vector2 ToVector2() const;

	__forceinline constexpr float Dot(const Vector3& InVector) const;
	__forceinline constexpr Vector3 Cross(const Vector3& InVector) const;

	// 정적멤버변수 
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 One;
	static const Vector3 Zero;
	static constexpr BYTE Dimension = 3;

	// 멤버변수
	union
	{
		struct
		{
			float X, Y, Z;
		};

		std::array<float, Dimension> Scalars = { 0.f, 0.f, 0.f };
	};
};

__forceinline constexpr float Vector3::operator[](BYTE InIndex) const
{
	assert(InIndex < Dimension);
	return Scalars[InIndex];
}

__forceinline constexpr float& Vector3::operator[](BYTE InIndex)
{
	assert(InIndex < Dimension);
	return Scalars[InIndex];
}

__forceinline constexpr Vector3 Vector3::operator-() const
{
	return Vector3(-X, -Y, -Z);

}
__forceinline constexpr Vector3 Vector3::operator*(float InScale) const
{
	return Vector3(X * InScale, Y * InScale, Z * InScale);
}

__forceinline constexpr Vector3 Vector3::operator/(float InScale) const
{
	return Vector3(X / InScale, Y / InScale, Z / InScale);
}

__forceinline constexpr Vector3 Vector3::operator*(const Vector3& InVector) const
{
	return Vector3(X * InVector.X, Y * InVector.Y, Z * InVector.Z);
}

__forceinline constexpr Vector3 Vector3::operator+(const Vector3& InVector) const
{
	return Vector3(X + InVector.X, Y + InVector.Y, Z + InVector.Z);
}

__forceinline constexpr Vector3 Vector3::operator-(const Vector3& InVector) const
{
	return Vector3(X - InVector.X, Y - InVector.Y, Z - InVector.Z);
}

__forceinline constexpr Vector3& Vector3::operator*=(float InScale)
{
	X *= InScale;
	Y *= InScale;
	Z *= InScale;
	return *this;
}

__forceinline constexpr Vector3& Vector3::operator/=(float InScale)
{
	X /= InScale;
	Y /= InScale;
	Z /= InScale;
	return *this;
}

__forceinline constexpr Vector3& Vector3::operator+=(const Vector3& InVector)
{
	X += InVector.X;
	Y += InVector.Y;
	Z += InVector.Z;
	return *this;
}

__forceinline constexpr Vector3& Vector3::operator-=(const Vector3& InVector)
{
	X -= InVector.X;
	Y -= InVector.Y;
	Z -= InVector.Z;
	return *this;
}

__forceinline constexpr Vector2 Vector3::ToVector2() const
{
	return Vector2(X, Y);
}

__forceinline constexpr float Vector3::Dot(const Vector3& InVector) const
{
	return X * InVector.X + Y * InVector.Y + Z * InVector.Z;
}

__forceinline constexpr Vector3 Vector3::Cross(const Vector3& InVector) const {
	return Vector3(
		Y * InVector.Z - Z * InVector.Y,
		Z * InVector.X - X * InVector.Z,
		X * InVector.Y - Y * InVector.X);
}