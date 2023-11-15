#pragma once

class CUI;
class CUIMgr
{
	SINGLE(CUIMgr)
private:
	CUI* m_pFocusedUI;

private:
	void ClickEvent(CUI* _pUI);
	CUI* GetTargetedUI(CUI* _pParentUI);

	CUI* FindFocusedUI();

public:
	// UI Ÿ���� Object�� Evnet���� ó���� ���⼭ ������
	void update();

};

