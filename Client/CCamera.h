#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera)
private:
	// ������Ʈ ��ġ - ī�޶� ��ġ �ؼ� �׷��ָ� �� 
	Vec2 m_vCameraPos;
	CObject* m_pParentObj;

	// ī�޶� ������ ���� 
	void MoveCamera();
public:
	
	void init();
	// ī�޶� ���� ó���� �ϱ� ���� update �ڵ� 
	void update();
	// ������Ʈ�� �������� �� ���Ǿ���� ���� ���ϴ� 
	Vec2 GetCalcPos();
	
public:
	void SetPos(Vec2 _vec) { m_vCameraPos = _vec; }
	Vec2 GetCameraPos() { return m_vCameraPos; }

	void SetObj(CObject* _obj) { m_pParentObj = _obj; }
};

