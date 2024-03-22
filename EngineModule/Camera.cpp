#include "Precompiled.h"

Camera::Camera(const ObjectInfo& Info):
	Object(Info)
{

}


Matrix4 Camera::GetViewMatrix() const
{

	switch (_Mode)
	{
	case CameraMode::Orthographic:


		break;
	case CameraMode::Perspective:
		break;
	default:
		break;
	}
	// ViewMatrix 만들어야함
	// Scale을 뺀 Rotation과 Transform 으로 만든 행렬의
	// 역행렬
	Vector3 pos = GetTransform().GetPosition();
	Vector3 viewX, viewY, viewZ;
	GetTransform().GetRotator().GetLocalAxes(viewX, viewY, viewZ);

	return Matrix4(
		Vector4(Vector3(viewX.X, viewY.X, viewZ.X), false), 
		Vector4(Vector3(viewX.Y, viewY.Y, viewZ.Y), false),
		Vector4(Vector3(viewX.Z, viewY.Z, viewZ.Z), false),
		Vector4(-viewX.Dot(pos), -viewY.Dot(pos), -viewZ.Dot(pos),1.0f)
	);
}

Matrix4 Camera::GetViewMatrixRotationOnly() const
{
	return Matrix4();
}

Matrix4 Camera::GetPerspectiveMatrix() const
{
	return Matrix4();
}

Matrix4 Camera::GetPerspectiveViewMatrix() const
{
	return Matrix4();
}
