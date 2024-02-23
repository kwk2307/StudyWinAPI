#pragma once

struct Vector4 {
public:
	constexpr Vector4() = default;
	explicit constexpr Vector4(const Vector2& InV, bool IsPoint = true) : X(InV.X), Y(InV.Y), Z(0.f) { W = IsPoint ? 1.f : 0.f; }
	explicit constexpr Vector4(const Vector3& InV, bool IsPoint = true) : X(InV.X), Y(InV.Y), Z(InV.Z) { W = IsPoint ? 1.f : 0.f; }
	explicit constexpr Vector4(int InX, int InY, int InZ, int InW) : X((float)InX), Y((float)InY), Z((float)InZ), W((float)InW) { };
	explicit constexpr Vector4(float InX, float InY, float InZ, float InW) : X(InX), Y(InY), Z(InZ), W(InW) { };

	// 연산자 
	 constexpr float operator[](BYTE InIndex) const;
	 constexpr float& operator[](BYTE InIndex);
	 constexpr Vector4 operator-() const;
	 constexpr Vector4 operator*(float InScale) const;
	 constexpr Vector4 operator/(float InScale) const;
	 constexpr Vector4 operator*(const Vector4& InVector) const;
	 constexpr Vector4 operator+(const Vector4& InVector) const;
	 constexpr Vector4 operator-(const Vector4& InVector) const;
	 constexpr Vector4& operator*=(float InScale);
	 constexpr Vector4& operator/=(float InScale);
	 constexpr Vector4& operator+=(const Vector4& InVector);
	 constexpr Vector4& operator-=(const Vector4& InVector);

	// 멤버함수 
	 constexpr Vector2 ToVector2() const { return Vector2(X, Y); }
	 constexpr Vector3 ToVector3() const { return Vector3(X, Y, Z); }
	 constexpr float Dot(const Vector4& InVector) const;

	// 정적멤버변수 
	static const Vector4 UnitX;
	static const Vector4 UnitY;
	static const Vector4 UnitZ;
	static const Vector4 UnitW;
	static const Vector4 One;
	static const Vector4 Zero;
	static constexpr BYTE Dimension = 4;

	// 멤버변수
	union
	{
		struct
		{
			float X, Y, Z, W;
		};

		std::array<float, Dimension> Scalars = { 0.f, 0.f, 0.f, 0.f };
	};
};

constexpr float Vector4::operator[](BYTE InIndex) const
{
	assert(InIndex < Dimension);
	return Scalars[InIndex];
}

constexpr float& Vector4::operator[](BYTE InIndex)
{
	assert(InIndex < Dimension);
	return Scalars[InIndex];
}

constexpr Vector4 Vector4::operator-() const
{
	return Vector4(-X, -Y, -Z, -W);
}

constexpr Vector4 Vector4::operator*(float InScale) const
{
	return Vector4(X * InScale, Y * InScale, Z * InScale, W * InScale);
}

constexpr Vector4 Vector4::operator/(float InScale) const
{
	return Vector4(X / InScale, Y / InScale, Z / InScale, W / InScale);
}

constexpr Vector4 Vector4::operator*(const Vector4& InVector) const
{
	return Vector4(X * InVector.X, Y * InVector.Y, Z * InVector.Z, W * InVector.W);
}

constexpr Vector4 Vector4::operator+(const Vector4& InVector) const
{
	return Vector4(X + InVector.X, Y + InVector.Y, Z + InVector.Z, W + InVector.W);
}

constexpr Vector4 Vector4::operator-(const Vector4& InVector) const
{
	return Vector4(X - InVector.X, Y - InVector.Y, Z - InVector.Z, W - InVector.W);
}

constexpr Vector4& Vector4::operator*=(float InScale)
{
	X *= InScale;
	Y *= InScale;
	Z *= InScale;
	W *= InScale;
	return *this;
}

constexpr Vector4& Vector4::operator/=(float InScale)
{
	X /= InScale;
	Y /= InScale;
	Z /= InScale;
	W /= InScale;
	return *this;
}

constexpr Vector4& Vector4::operator+=(const Vector4& InVector)
{
	X += InVector.X;
	Y += InVector.Y;
	Z += InVector.Z;
	W += InVector.W;
	return *this;
}

constexpr Vector4& Vector4::operator-=(const Vector4& InVector)
{
	X -= InVector.X;
	Y -= InVector.Y;
	Z -= InVector.Z;
	W -= InVector.W;
	return *this;
}

constexpr float Vector4::Dot(const Vector4& InVector) const
{
	return X * InVector.X + Y * InVector.Y + Z * InVector.Z + W * InVector.W;
}
