#pragma once

class CUI;
class CUIMgr
{
	SINGLE(CUIMgr)

private:
	bool ClickEvent(CUI* _pUI);
	CUI* GetTargetedUI(CUI* _pParentUI);
public:
	// UI Ÿ���� Object�� Evnet���� ó���� ���⼭ ������
	void update();

};

