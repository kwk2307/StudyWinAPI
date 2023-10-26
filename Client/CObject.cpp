#include "pch.h"
#include "CObject.h"

#include "CCollider.h"

CObject::CObject() :
	m_vPos{ 0,0 },
	m_vScale{ 0,0 },
	m_pCollider(nullptr)
{
}

CObject::~CObject()
{
	if (m_pCollider != nullptr) {
		delete m_pCollider;
	}
}


void CObject::CreateCollider()
{
	if (m_pCollider == nullptr) {
		m_pCollider = new CCollider;
		m_pCollider->m_pOwner = this;
	}
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
