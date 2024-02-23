#pragma once

struct Vector3 {
public:
	constexpr Vector3() = default;
	explicit constexpr Vector3(const Vector2& InV, bool IsPoint = true) : X(InV.X), Y(InV.Y) { Z = IsPoint ? 1.f : 0.f; }
	explicit constexpr Vector3(int InX, int InY, int InZ) : X((float)InX), Y((float)InY), Z((float)InZ) { };
	explicit constexpr Vector3(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) { };

	// 연산자 
	 constexpr float operator[](BYTE InIndex) const;
	 constexpr float& operator[](BYTE InIndex);
	 constexpr Vector3 operator-() const;
	 constexpr Vector3 operator*(float InScale) const;
	 constexpr Vector3 operator/(float InScale) const;
	 constexpr Vector3 operator*(const Vector3& InVector) const;
	 constexpr Vector3 operator+(const Vector3& InVector) const;
	 constexpr Vector3 operator-(const Vector3& InVector) const;
	 constexpr Vector3& operator*=(float InScale);
	 constexpr Vector3& operator/=(float InScale);
	 constexpr Vector3& operator+=(const Vector3& InVector);
	 constexpr Vector3& operator-=(const Vector3& InVector);


	// 맴버 함수 
	 constexpr Vector2 ToVector2() const;
	 constexpr float Dot(const Vector3& InVector) const;

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
