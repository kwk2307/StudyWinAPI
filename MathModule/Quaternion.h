#pragma once
struct Quaternion 
{
public:
	__forceinline constexpr Quaternion() = default;
	__forceinline explicit constexpr Quaternion(float InX, float InY, float InZ, float InW) :
	X(InX),Y(InY),Z(InZ),W(InW)
	{}
	
	__forceinline explicit constexpr Quaternion(const Vector3& InAxis, float InAngleDegree) {
		FromAxisAngle(InAxis, InAngleDegree);
	}
	__forceinline constexpr void FromAxisAngle(const Vector3& InAxis, float InAngleDegree);

	//연산자 
	__forceinline constexpr Quaternion operator*(const Quaternion& InQuaternion) const;
	__forceinline constexpr Vector3 operator*(const Vector3& InVector) const;

	// 계산
	__forceinline constexpr Vector3 RotateVector(const Vector3& InVector) const;
	__forceinline constexpr void FromRotator(const Rotator& InRot);
	
	__forceinline constexpr float RealPart() const { return W; }
	__forceinline constexpr Vector3 ImaginaryPart() const { return Vector3(X, Y, Z); }
public:
	float X = 0.f;
	float Y = 0.f;
	float Z = 0.f;
	float W = 0.f;
};

__forceinline constexpr void Quaternion::FromAxisAngle(const Vector3& InAxis, float InAngleDegree)
{
	float sin = 0.f, cos = 0.f;
	MathUtil::GetSinCos(sin, cos, InAngleDegree * 0.5f);
	W = cos;
	X = sin * InAxis.X;
	Y = sin * InAxis.Y;
	Z = sin * InAxis.Z;
}

inline constexpr Quaternion Quaternion::operator*(const Quaternion& InQuaternion) const
{
	Quaternion result;
	Vector3 v1(X, Y, Z), v2(InQuaternion.X, InQuaternion.Y, InQuaternion.Z);
	result.W = W * InQuaternion.W - v1.Dot(v2);
	Vector3 v = v2 * W + v1 * InQuaternion.W + v1.Cross(v2);
	result.X = v.X;
	result.Y = v.Y;
	result.Z = v.Z;

	return result;
}

inline constexpr Vector3 Quaternion::operator*(const Vector3& InVector) const
{
	return RotateVector(InVector);
}

__forceinline constexpr Vector3 Quaternion::RotateVector(const Vector3& InVector) const
{
	Vector3 q(X, Y, Z);
	Vector3 t = q.Cross(InVector) * 2.f;
	Vector3 result = InVector + (t * W) + q.Cross(t);
	return result;
}

__forceinline constexpr void Quaternion::FromRotator(const Rotator& InRot)
{
	float sinPitch = 0.f, sinYaw = 0.f, sinRoll = 0.f;
	float cosPitch = 0.f, cosYaw = 0.f, cosRoll = 0.f;
	
	MathUtil::GetSinCos(sinPitch, cosPitch, InRot.Pitch * 0.5f);
	MathUtil::GetSinCos(sinYaw, cosYaw, InRot.Yaw * 0.5f);
	MathUtil::GetSinCos(sinRoll, cosRoll, InRot.Roll * 0.5f);

	W = sinYaw * sinPitch * sinRoll + cosYaw * cosPitch * cosRoll;
	X = sinYaw * sinRoll * cosPitch + sinPitch * cosYaw * cosRoll;
	Y = sinYaw * cosPitch * cosRoll - sinPitch * sinRoll * cosYaw;
	Z = -sinYaw * sinPitch * cosRoll + sinRoll * cosYaw * cosPitch;
}
