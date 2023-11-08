#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera)
private:
	// 오브젝트 위치에서 맴버 만큼 떨어진 값을 계산해서
	// 그만큼 더해준 값에 그려줌 

	Vec2 m_vCameraPos;

	void MoveCamera();
	
public:
	void update();


};

