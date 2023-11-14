#pragma once
class CSetBrushPen
{
private:
	HDC m_hDC;
	HBRUSH m_hDefaultBrush;
	HPEN m_hDefaultPen;

public:

	CSetBrushPen(HDC _hDC, BrushType _eBrushType, PenType _ePenType);
	~CSetBrushPen();
};

