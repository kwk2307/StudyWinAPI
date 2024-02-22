#pragma once

struct Vector3 {
public:
	constexpr Vector3() = default;
	explicit constexpr Vector3(const Vector2& InV, bool IsPoint = true) : X(InV.X), Y(InV.Y) { Z = IsPoint ? 1.f : 0.f; }
	explicit constexpr Vector3(int InX, int InY, int InZ) : X((float)InX), Y((float)InY), Z((float)InZ) { };
	explicit constexpr Vector3(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) { };

	// ������ 
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


	// �ɹ� �Լ� 
	 constexpr Vector2 ToVector2() const;
	 constexpr float Dot(const Vector3& InVector) const;

	// ����������� 
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 One;
	static const Vector3 Zero;
	static constexpr BYTE Dimension = 3;

	// �������
	union
	{
		struct
		{
			float X, Y, Z;
		};

		std::array<float, Dimension> Scalars = { 0.f, 0.f, 0.f };
	};
};