#include "pch.h"
#include "CUI.h"

#include "CKeyMgr.h"

#include "CSetBrushPen.h"


CUI::CUI():
	m_pParentUI(nullptr),
	m_vecUI{},
	m_vOffset{},
	m_bClickable(false),
	m_bOnMouse(false),
	m_eState(UIState::None)
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
		// 현재 UI가 최상단 UI 이다.
		SetPos(m_vOffset);
	}

	Vec2 vPos = this->GetPos();
	Vec2 vScale = this->GetScale();

	Vec2 vMousPos = MOUSEPOS;

	m_bOnMouse = (
		vPos.x + (vScale.x / 2) > vMousPos.x &&
		vPos.x - (vScale.x / 2) < vMousPos.x &&
		vPos.y + (vScale.y / 2) > vMousPos.y &&
		vPos.y - (vScale.y / 2) < vMousPos.y);

	for (vector<CUI*>::iterator iter = m_vecUI.begin(); iter != m_vecUI.end(); ++iter) {
		(*iter)->finalEvnet();
	}
}

void CUI::update()
{
	for (vector<CUI*>::iterator iter = m_vecUI.begin(); iter != m_vecUI.end(); ++iter) {
		(*iter)->update();
	}
}

void CUI::render(HDC _dc)
{
	Vec2 vRenderPos = GetPos();
	Vec2 vRenderScale = GetScale();

	switch (m_eState)
	{
	case UIState::None:
		Rectangle(_dc,
			(int)(vRenderPos.x - vRenderScale.x / 2),
			(int)(vRenderPos.y - vRenderScale.y / 2),
			(int)(vRenderPos.x + vRenderScale.x / 2),
			(int)(vRenderPos.y + vRenderScale.y / 2)
		);
		break;
	case UIState::Hover:
	{
		CSetBrushPen bp(_dc, BrushType::HOLLOW, PenType::RED);
		Rectangle(_dc,
			(int)(vRenderPos.x - vRenderScale.x / 2),
			(int)(vRenderPos.y - vRenderScale.y / 2),
			(int)(vRenderPos.x + vRenderScale.x / 2),
			(int)(vRenderPos.y + vRenderScale.y / 2)
		);
		break;
	}
	case UIState::Clicked:
	{
		CSetBrushPen bp(_dc, BrushType::HOLLOW, PenType::BLUE);
		Rectangle(_dc,
			(int)(vRenderPos.x - vRenderScale.x / 2),
			(int)(vRenderPos.y - vRenderScale.y / 2),
			(int)(vRenderPos.x + vRenderScale.x / 2),
			(int)(vRenderPos.y + vRenderScale.y / 2)
		);
		break;
	}
	case UIState::Disable:
		break;
	default:
		break;
	}

	for (vector<CUI*>::iterator iter = m_vecUI.begin(); iter != m_vecUI.end(); ++iter) {
		(*iter)->render(_dc);
	}
}
