#pragma once

class CObject;
class CCollider
{

private:
	CObject* m_pOwner;
	Vec2 m_vOffsetPos;
	Vec2 m_vFinalPos;

	Vec2 m_vScale;

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }


public:
	void finalupdate();
	void render(HDC _dc);

public:
	CCollider();
	~CCollider();

	friend class CObject;

};

