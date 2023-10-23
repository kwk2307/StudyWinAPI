#pragma once

class CObject
{
private:
	// 위치 정보
	// 크기 정보
	Vec2 m_Position;
	Vec2 m_Scale;

public:
	void SetPos(Vec2 _pos) {m_Position = _pos;}
	Vec2 GetPos() {return m_Position;}

	void SetScale(Vec2 _scale) {m_Scale = _scale;}
	Vec2 GetScale() {return m_Scale;}

	virtual void update() = 0;
	virtual void render(HDC _hdc) = 0;
public:
	CObject();
	~CObject();

};

