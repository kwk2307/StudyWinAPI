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
	// UI 타입의 Object의 Evnet관련 처리를 여기서 수행함
	void update();

};

