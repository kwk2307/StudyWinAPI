#include "pch.h"
#include "CObject.h"


CObject::CObject() :
	m_Position{ 0,0 },
	m_Scale{ 0,0 }
{
}

CObject::~CObject()
{
}


void CObject::render(HDC _hdc)
{
	Rectangle(_hdc,
		int(GetPos().x - GetScale().x / 2),
		int(GetPos().y - GetScale().y / 2),
		int(GetPos().x + GetScale().x / 2),
		int(GetPos().y + GetScale().y / 2)
	);
}
