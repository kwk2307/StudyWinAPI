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
    const ScreenPoint& GetViewPortSize() const { return _ViewportSize; }

    void SetViewportSize(const ScreenPoint& InViewportSize) { _ViewportSize = InViewportSize; }

    // ��� ����
     Matrix4 GetViewMatrix() const;
     Matrix4 GetViewMatrixRotationOnly() const;
     Matrix4 GetProjectionMatrix() const;
     Matrix4 GetProjectionViewMatrix() const;

private:
    CameraMode _Mode = CameraMode::Orthographic;
    // ��ũ�� ������

    float _FOV = 60.f;
    float _NearZ = 5.5f;
    float _FarZ = 5000.f;
    ScreenPoint _ViewportSize;
};

