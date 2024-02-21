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