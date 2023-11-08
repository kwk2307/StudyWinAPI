#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera)
private:
	// 오브젝트 위치 - 카메라 위치 해서 그려주면 됨 
	Vec2 m_vCameraPos;
	CObject* m_pParentObj;

	// 카메라 움직임 구현 
	void MoveCamera();
public:
	
	void init();
	// 카메라에 대한 처리를 하기 위한 update 코드 
	void update();
	// 오브젝트를 렌더링할 때 계산되어야할 값을 구하는 
	Vec2 GetCalcPos();
	
public:
	void SetPos(Vec2 _vec) { m_vCameraPos = _vec; }
	Vec2 GetCameraPos() { return m_vCameraPos; }

	void SetObj(CObject* _obj) { m_pParentObj = _obj; }
};

