#include "pch.h"
#include "CSetBrushPen.h"

#include "CCore.h"

CSetBrushPen::CSetBrushPen(HDC _hDC, BrushType _eBrushType, PenType _ePenType) :
	m_hDC(_hDC),
	m_hDefaultBrush(nullptr),
	m_hDefaultPen(nullptr)
{
	m_hDefaultBrush = (HBRUSH)SelectObject(m_hDC,CCore::GetInstance()->getBrush(_eBrushType));
	m_hDefaultPen = (HPEN)SelectObject(m_hDC, CCore::GetInstance()->getPen(_ePenType));
}

CSetBrushPen::~CSetBrushPen()
{
	SelectObject(m_hDC, m_hDefaultBrush);
	SelectObject(m_hDC, m_hDefaultPen);
}
