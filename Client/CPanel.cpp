#include "pch.h"
#include "CPanel.h"

#include "CKeyMgr.h"

void CPanel::OnMouseTap()
{
	m_vPreMousePos = MOUSEPOS;
}

void CPanel::OnMouseAway()
{

}

void CPanel::OnMouseHold()
{
	Vec2 vMousePos = MOUSEPOS;

	SetOffset(GetOffset() - (m_vPreMousePos - vMousePos));
	m_vPreMousePos = vMousePos;

}
