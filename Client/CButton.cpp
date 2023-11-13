#include "pch.h"
#include "CButton.h"

#include "CKeyMgr.h"

CButton::CButton() :
	m_eState(None)
{
	SetClickable(true);
}

CButton::~CButton()
{

}

void CButton::update()
{

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Vec2 vMousPos = MOUSEPOS;

	bool bOnMouse = (
		vPos.x + (vScale.x / 2) > vMousPos.x &&
		vPos.x - (vScale.x / 2) < vMousPos.x &&
		vPos.y + (vScale.y / 2) > vMousPos.y &&
		vPos.y - (vScale.y / 2) < vMousPos.y);

	if (bOnMouse && GetClickable()) {
		if (KEYCHKCK_TAP(KEY::LBUTTON)) {
			m_eState = CButton::Clicked;
		}
		else if (KEYCHKCK_HOLD(KEY::LBUTTON)) {
			m_eState = CButton::Clicked;
		}
		else if(KEYCHKCK_AWAY(KEY::LBUTTON)) {
			m_eState = CButton::Hover;
			OnButtonClick();
		}
		else {
			m_eState = CButton::Hover;
		}
	}
	else {
		m_eState = CButton::None;
	}

}

void CButton::OnButtonClick()
{

}
