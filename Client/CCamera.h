#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera)
private:
	// ������Ʈ ��ġ���� �ɹ� ��ŭ ������ ���� ����ؼ�
	// �׸�ŭ ������ ���� �׷��� 

	Vec2 m_vCameraPos;

	void MoveCamera();
	
public:
	void update();


};

