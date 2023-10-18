#pragma once

class CObject
{
private:
	// 위치 정보
	// 크기 정보
	Vec2 m_Position;
	Vec2 m_Scale;

public:
	void SetPos(Vec2 _pos);
	Vec2 GetPos();

	void SetScale(Vec2 _scale);
	Vec2 GetScale();

	void update();
	void render();
public:
	CObject();
	~CObject();

};

