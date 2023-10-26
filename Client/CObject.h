#pragma once

class CCollider;

class CObject
{
private:
	// 위치 정보
	// 크기 정보
	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;

public:
	void SetPos(Vec2 _pos) { m_vPos = _pos;}
	Vec2 GetPos() {return m_vPos;}

	void SetScale(Vec2 _scale) { m_vPos = _scale;}
	Vec2 GetScale() {return m_vScale;}

	CCollider* GetCollider() { return m_pCollider; }

	void CreateCollider();

	virtual void update() = 0;
	virtual void finalupdate() final;

	virtual void render(HDC _dc);
	void component_render(HDC _dc);

public:
	CObject();
	~CObject();

};

