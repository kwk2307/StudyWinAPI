#include "Precompiled.h"

Camera::Camera(const ObjectInfo& Info):
	Object(Info)
{

}

void Camera::GetViewAxes(Vector3& OutViewX, Vector3& OutViewY, Vector3& OutViewZ) const
{
	// 로컬 Z축 값의 반대 방향을 뷰 공간의 Z축으로 설정
	OutViewZ = -GetTransform().GetLocalZ();
	OutViewY = GetTransform().GetLocalY();
	OutViewX = -GetTransform().GetLocalX();
}

Matrix4 Camera::GetViewMatrix() const
{
	return Matrix4();
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
