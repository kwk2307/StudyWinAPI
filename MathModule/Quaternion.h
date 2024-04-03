#pragma once
struct Quaternion 
{
// 자유로운 회전을 위해서는 사원수나 로드리게스 회전공식에 의한 회전이 필요
public:
	__forceinline constexpr Quaternion() = default;
	__forceinline explicit constexpr Quaternion(float InX, float InY, float InZ, float InW) :
	X(InX),Y(InY),Z(InZ),W(InW)
	{}
	__forceinline explicit constexpr Quaternion(const Vector3& InAxis, float InAngleDegree) {
		FromAxisAngle(InAxis, InAngleDegree);
	}
	__forceinline explicit constexpr Quaternion(const Rotator& InRot) {
		FromRotator(InRot);
	}
	__forceinline explicit Quaternion(const Matrix3& InMatrix) {
		FromMatrix(InMatrix);
	}

	__forceinline void FromMatrix(const Matrix3& InMatrix);
	__forceinline constexpr void FromAxisAngle(const Vector3& InAxis, float InAngleDegree);
	__forceinline constexpr void FromRotator(const Rotator& InRot);

	//연산자 
	__forceinline constexpr Quaternion operator*(const Quaternion& InQuaternion) const;
	__forceinline constexpr Vector3 operator*(const Vector3& InVector) const;

	// 계산
	__forceinline constexpr Vector3 RotateVector(const Vector3& InVector) const;
	
	
	__forceinline constexpr Rotator ToRotator()const;
	__forceinline constexpr float RealPart() const { return W; }
	__forceinline constexpr Vector3 ImaginaryPart() const { return Vector3(X, Y, Z); }
public:
	float X = 0.f;
	float Y = 0.f;
	float Z = 0.f;
	float W = 0.f;
};

__forceinline void Quaternion::FromMatrix(const Matrix3& InMatrix)
{
	// 켄 슈메이크 알고리즘
	float trace = InMatrix[0][0] + InMatrix[1][1] + InMatrix[2][2];
	
	if (trace > 0.f) {

		// W의 값을 통해 xyz륵 계산
		float root = sqrtf(trace + 1.f);
		W = 0.5f * root;
		root = 0.5f / root;

		X = (InMatrix[1][2] - InMatrix[2][1]) * root;
		Y = (InMatrix[2][0] - InMatrix[0][2]) * root;
		Z = (InMatrix[0][1] - InMatrix[1][0]) * root;
	}
	else {
		BYTE i = 0;

		// X,Y,Z 중에서 가장 큰 요소를 파악
		if (InMatrix[1][1] > InMatrix[0][0]) { i = 1; }
		if (InMatrix[2][2] > InMatrix[i][i]) { i = 2; }

		// i, j, k 의 순서 지정
		static const BYTE next[3] = { 1, 2, 0 };
		BYTE j = next[i];
		BYTE k = next[j];

		// 가장 큰 요소의 값을 구하기
		float root = sqrtf(InMatrix[i][i] - InMatrix[j][j] - InMatrix[k][k] + 1.f);

		float* qt[3] = { &X, &Y, &Z };
		*qt[i] = 0.5f * root;

		root = 0.5f / root;

		// 나머지 두 요소의 값을 구하기
		*qt[j] = (InMatrix[i][j] + InMatrix[j][i]) * root;
		*qt[k] = (InMatrix[i][k] + InMatrix[k][i]) * root;

		// 마지막 W 값 구하기
		W = (InMatrix[j][k] - InMatrix[k][j]) * root;
	}
}

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

__forceinline constexpr Rotator Quaternion::ToRotator() const
{
	Rotator result;
	float sinrCosp = 2 * (W * Z + X * Y);
	float cosrCosp = 1 - 2 * (Z * Z + X * X);
	result.Roll = MathUtil::Rad2Deg(atan2f(sinrCosp, cosrCosp));

	float pitchTest = W * X - Y * Z;
	float asinThreshold = 0.4999995f;
	float sinp = 2 * pitchTest;
	if (pitchTest < -asinThreshold)
	{
		result.Pitch = -90.f;
	}
	else if (pitchTest > asinThreshold)
	{
		result.Pitch = 90.f;
	}
	else
	{
		result.Pitch = MathUtil::Rad2Deg(asinf(sinp));
	}

	float sinyCosp = 2 * (W * Y + X * Z);
	float cosyCosp = 1.f - 2 * (X * X + Y * Y);
	result.Yaw = MathUtil::Rad2Deg(atan2f(sinyCosp, cosyCosp));

	return result;
}
