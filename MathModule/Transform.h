#pragma once

struct Transform
{
public:
	constexpr Transform() = default;
	constexpr Transform(const Vector3& InPosition) : Position(InPosition) { }
	constexpr Transform(const Vector3& InPosition, const Rotator& InRotation) : Position(InPosition), Rotation(InRotation) { }
	constexpr Transform(const Vector3& InPosition, const Rotator& InRotation, const Vector3& InScale) : Position(InPosition), Rotation(InRotation), Scale(InScale) { }
	Transform(const Matrix4& InMatrix);

public: // 트랜스폼 설정함수
	constexpr void SetPosition(const Vector3& InPosition) { Position = InPosition; }
	constexpr void AddPosition(const Vector3& InDeltaPosition) { Position += InDeltaPosition; }
	void AddYawRotation(float InDegree)
	{
		Rotation.Yaw += InDegree;
		Rotation.Clamp();
	}
	void AddRollRotation(float InDegree)
	{
		Rotation.Roll += InDegree;
		Rotation.Clamp();
	}
	void AddPitchRotation(float InDegree)
	{
		Rotation.Pitch += InDegree;
		Rotation.Clamp();
	}

	constexpr void SetRotation(const Rotator& InRot) { Rotation = InRot; }

	constexpr void SetScale(const Vector3& InScale) { Scale = InScale; }

	constexpr Matrix4 GetMatrix() const;

	constexpr Vector3 GetPosition() const { return Position; }
	constexpr Rotator GetRotation() const { return Rotation; }
	constexpr Vector3 GetScale() const { return Scale; }

private: // 트랜스폼에 관련된 변수
	Vector3 Position;
	Rotator Rotation;
	Vector3 Scale = Vector3::One;

};

constexpr Matrix4 Transform::GetMatrix() const
{
	Vector3 XAxis, YAxis, ZAxis;
	GetRotation().GetLocalAxes(XAxis,YAxis,ZAxis);
	return Matrix4(
		Vector4(XAxis * Scale.X, false),
		Vector4(YAxis * Scale.Y, false),
		Vector4(ZAxis * Scale.Z, false),
		Vector4(Position, true)
	);
}

