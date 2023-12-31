#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"
#include "CCamera.h"

#include "CSetBrushPen.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider():
	m_pOwner(nullptr),
	m_iID(g_iNextID++)
{
}

CCollider::CCollider(const CCollider& _origin):
	m_pOwner(nullptr),
	m_vOffsetPos(_origin.m_vOffsetPos),
	m_vScale(_origin.m_vScale),
	m_iID(g_iNextID++)
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
	Vec2 vRenderPos = m_vFinalPos - CCamera::GetInstance()->GetCalcPos();

	CSetBrushPen bp(_dc, BrushType::HOLLOW, PenType::RED);

	Rectangle(_dc,
		int(vRenderPos.x - m_vScale.x / 2.f),
		int(vRenderPos.y - m_vScale.y / 2.f),
		int(vRenderPos.x + m_vScale.x / 2.f),
		int(vRenderPos.y + m_vScale.y / 2.f)
	);
}

void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::BeginCollision(CCollider* _pOther)
{
	m_pOwner->BeginCollision(_pOther);
}

void CCollider::EndCollision(CCollider* _pOther)
{
	m_pOwner->EndCollision(_pOther);
}
