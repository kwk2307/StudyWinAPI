#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"

#include "CSetBrushPen.h"

CCollider::CCollider():
	m_pOwner(nullptr),
	m_vFinalPos{},
	m_vOffsetPos{},
	m_vScale{}
{
}

CCollider::~CCollider()
{
}


void CCollider::finalupdate()
{
	Vec2 vObjectPos = m_pOwner->GetPos();

	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void CCollider::render(HDC _dc)
{
	CSetBrushPen bp(_dc, BrushType::HOLLOW, PenType::RED);

	Rectangle(_dc,
		int(m_vFinalPos.x - m_vScale.x / 2.f),
		int(m_vFinalPos.y - m_vScale.y / 2.f),
		int(m_vFinalPos.x + m_vScale.x / 2.f),
		int(m_vFinalPos.y + m_vScale.y / 2.f)
	);
}
