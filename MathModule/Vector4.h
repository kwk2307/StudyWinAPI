#pragma once

struct Vector4 {
public:
	constexpr Vector4() = default;
	explicit constexpr Vector4(const Vector2& InV, bool IsPoint = true) : X(InV.X), Y(InV.Y), Z(0.f) { W = IsPoint ? 1.f : 0.f; }
	explicit constexpr Vector4(const Vector3& InV, bool IsPoint = true) : X(InV.X), Y(InV.Y), Z(InV.Z) { W = IsPoint ? 1.f : 0.f; }
	explicit constexpr Vector4(int InX, int InY, int InZ, int InW) : X((float)InX), Y((float)InY), Z((float)InZ), W((float)InW) { };
	explicit constexpr Vector4(float InX, float InY, float InZ, float InW) : X(InX), Y(InY), Z(InZ), W(InW) { };

	// 연산자 
	____forceinline constexpr float operator[](BYTE InIndex) const;
	____forceinline constexpr float& operator[](BYTE InIndex);
	____forceinline constexpr Vector4 operator-() const;
	____forceinline constexpr Vector4 operator*(float InScale) const;
	____forceinline constexpr Vector4 operator/(float InScale) const;
	____forceinline constexpr Vector4 operator*(const Vector4& InVector) const;
	____forceinline constexpr Vector4 operator+(const Vector4& InVector) const;
	____forceinline constexpr Vector4 operator-(const Vector4& InVector) const;
	____forceinline constexpr Vector4& operator*=(float InScale);
	____forceinline constexpr Vector4& operator/=(float InScale);
	____forceinline constexpr Vector4& operator+=(const Vector4& InVector);
	____forceinline constexpr Vector4& operator-=(const Vector4& InVector);


	____forceinline constexpr float Dot(const Vector4& InVector) const;

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