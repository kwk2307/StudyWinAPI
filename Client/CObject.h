#pragma once

class CCollider;
class CAnimator;

class CObject
{
private:
	// 위치 정보
	// 크기 정보
	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;
	CAnimator* m_pAnimator;

	bool m_bDead;
public:
	void SetPos(Vec2 _pos) { m_vPos = _pos;}
	Vec2 GetPos() {return m_vPos;}

	void SetScale(Vec2 _scale) { m_vScale = _scale;}
	Vec2 GetScale() {return m_vScale;}

public:
	CCollider* GetCollider() { return m_pCollider; }
	void CreateCollider();
	
	CAnimator* GetAnimator() { return m_pAnimator; }
	void CreateAnimator();

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void BeginCollision(CCollider* _pOther);
	virtual void EndCollision(CCollider* _pOther);

public:
	void SetDead(bool _state) { m_bDead = _state; }
	bool GetDead() { return m_bDead; }

public:
	virtual void update() = 0;
	virtual void finalupdate() final;

	virtual void render(HDC _dc);
	void component_render(HDC _dc);

public:
	 CObject();
	~CObject();

	CObject(const CObject& origin);

};

