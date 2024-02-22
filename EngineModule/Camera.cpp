#include "Precompiled.h"

Camera::Camera(const ObjectInfo& Info):
	Object(Info)
{

}


Matrix4 Camera::GetViewMatrix() const
{
	return Matrix4(
		Vector4::UnitX,
		Vector4::UnitY,
		Vector4::UnitZ,
		Vector4::Zero
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
