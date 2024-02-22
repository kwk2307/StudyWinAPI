#pragma once
class TransformComponent
{
public:
	TransformComponent() = default;

	constexpr Vector3 GetXAxis() const { return; }

private:
	Vector3 _Position = Vector3::Zero;
	Rotator _Rotation;
	Vector3 _Scale = Vector3::One;

	Vector3 _Right = Vector3::UnitX;
	Vector3 _Up = Vector3::UnitY;
	Vector3 _Forward = Vector3::UnitZ;
};

