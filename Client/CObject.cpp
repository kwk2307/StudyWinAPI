#include "pch.h"
#include "CObject.h"

#include "CCollider.h"
#include "CAnimator.h"

#include "CSetBrushPen.h"

CObject::CObject() :
	m_pAnimator(nullptr),
	m_vPos{ 0,0 },
	m_vScale{ 0,0 },
	m_pCollider(nullptr),
	m_bDead(false)
{
}

CObject::~CObject()
{
	if (m_pCollider != nullptr) {
		delete m_pCollider;
	}
	if (m_pAnimator != nullptr) {
		delete m_pAnimator;
	}
}

CObject::CObject(const CObject& origin) :
	m_pAnimator(nullptr),
	m_vPos(origin.m_vPos),
	m_vScale(origin.m_vScale),
	m_pCollider(nullptr),
	m_bDead(false)
{
	if (origin.m_pCollider != nullptr) {
		m_pCollider = new CCollider(*origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}

	if (origin.m_pAnimator != nullptr) {
		m_pAnimator = new CAnimator(*origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
}

void CObject::CreateCollider()
{
	if (m_pCollider == nullptr) {
		m_pCollider = new CCollider;
		m_pCollider->m_pOwner = this;
	}
}

void CObject::CreateAnimator()
{
	if (m_pAnimator == nullptr) {
		m_pAnimator = new CAnimator;
		m_pAnimator->m_pOwner = this;
	}
}

void CObject::OnCollision(CCollider* _pOther)
{
}

void CObject::BeginCollision(CCollider* _pOther)
{
}

void CObject::EndCollision(CCollider* _pOther)
{
}

void CObject::finalupdate()
{
	if (m_pCollider != nullptr) {
		m_pCollider->finalupdate();
	}
}

void CObject::render(HDC _dc)
{
	Rectangle(_dc,
		int(m_vPos.x - m_vScale.x / 2.f),
		int(m_vPos.y - m_vScale.y / 2.f),
		int(m_vPos.x + m_vScale.x / 2.f),
		int(m_vPos.y + m_vScale.y / 2.f)
	);
	component_render(_dc);
}

void CObject::component_render(HDC _dc)
{
	if (m_pCollider != nullptr) {
		m_pCollider->render(_dc);
	}
}
