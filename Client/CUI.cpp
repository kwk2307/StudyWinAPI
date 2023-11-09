#include "pch.h"
#include "CUI.h"

CUI::CUI():
	m_pParentUI(nullptr),
	m_vecUI{},
	m_vOffset{}
{
}

CUI::~CUI() {
}

void CUI::finalEvnet()
{
	if (m_pParentUI != nullptr) {
		 SetPos(m_pParentUI->GetPos() + m_vOffset);
	}
	else {
		// ���� UI�� �ֻ�� UI �̴�.
		SetPos(m_vOffset);
	}

	for (vector<CUI*>::iterator iter = m_vecUI.begin(); iter != m_vecUI.end(); ++iter) {
		(*iter)->finalEvnet();
	}
}

void CUI::update()
{
	// updaet�ϸ鼭 �� ó��

	for (vector<CUI*>::iterator iter = m_vecUI.begin(); iter != m_vecUI.end(); ++iter) {
		(*iter)->update();
	}
}

void CUI::render(HDC _dc)
{
	Vec2 vRenderPos = GetPos();
	Vec2 vRenderScale = GetScale();

	Rectangle(_dc,
		vRenderPos.x - vRenderScale.x / 2,
		vRenderPos.y - vRenderScale.y / 2,
		vRenderPos.x + vRenderScale.x / 2,
		vRenderPos.y + vRenderScale.y / 2
	);

	for (vector<CUI*>::iterator iter = m_vecUI.begin(); iter != m_vecUI.end(); ++iter) {
		(*iter)->render(_dc);
	}
}
