#pragma once

class CCollider;

class CObject
{
private:
	// ��ġ ����
	// ũ�� ����
	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;

	bool m_bDead;
public:
	void SetPos(Vec2 _pos) { m_vPos = _pos;}
	Vec2 GetPos() {return m_vPos;}

	void SetScale(Vec2 _scale) { m_vPos = _scale;}
	Vec2 GetScale() {return m_vScale;}

public:
	CCollider* GetCollider() { return m_pCollider; }
	void CreateCollider();

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

};

