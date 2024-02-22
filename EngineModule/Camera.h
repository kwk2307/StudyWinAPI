#pragma once

enum class CameraMode
{
    Orthographic = 0,
    Perspective
};


class Camera :
    public Object
{
public:
    Camera(const ObjectInfo& Info);

    // ��� ����
     Matrix4 GetViewMatrix() const;
     Matrix4 GetViewMatrixRotationOnly() const;
     Matrix4 GetPerspectiveMatrix() const;
     Matrix4 GetPerspectiveViewMatrix() const;

private:
    CameraMode _Mode = CameraMode::Orthographic;
    // ��ũ�� ������

    float _FOV = 60.f;
    float _NearZ = 5.5f;
    float _FarZ = 5000.f;
    ScreenPoint _ViewportSize;
};

