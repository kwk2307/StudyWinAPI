#pragma once

class CUI;
class CUIMgr
{
	SINGLE(CUIMgr)

private:
	void ClickEvent(CUI* _pUI);
	CUI* GetTargetedUI(CUI* _pParentUI);
public:
	// UI Ÿ���� Object�� Evnet���� ó���� ���⼭ ������
	void update();

};

