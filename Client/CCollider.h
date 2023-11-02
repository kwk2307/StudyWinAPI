#pragma once

class CObject;
class CCollider
{

private:
	static UINT g_iNextID;

	CObject* m_pOwner;
	Vec2 m_vOffsetPos;
	Vec2 m_vFinalPos;
	Vec2 m_vScale;

	UINT m_iID;

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	Vec2 GetFinalPos() { return m_vFinalPos; }

	UINT GetID() { return m_iID;}
	CObject* GetOwner() { return m_pOwner; }

public:
	void finalupdate();
	void render(HDC _dc);

	//대입 연산자 삭제 
	CCollider& operator = (CCollider& _Collider) = delete;

public: 
	void OnCollision(CCollider* _pOther);
	void BeginCollision(CCollider* _pOther);
	void EndCollision(CCollider* _pOther);

public:
	CCollider();
	//복사 생성자 직접 구현
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;

};

