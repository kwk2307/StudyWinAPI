#include "pch.h"
#include "CObject.h"

void CObject::SetPos(Vec2 _pos)
{
	m_Position = _pos;
}

Vec2 CObject::GetPos()
{
	return m_Position;
}

void CObject::SetScale(Vec2 _scale)
{
	m_Scale = _scale;
}

Vec2 CObject::GetScale()
{
	return m_Scale;
}

void CObject::update()
{

}

void CObject::render()
{
}

CObject::CObject() :
	m_Position{ 0,0 },
	m_Scale{ 0,0 }
{

}

CObject::~CObject()
{

}
