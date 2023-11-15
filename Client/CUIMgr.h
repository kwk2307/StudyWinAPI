#pragma once

class CUI;
class CUIMgr
{
	SINGLE(CUIMgr)

private:
	bool ClickEvent(CUI* _pUI);
	CUI* GetTargetedUI(CUI* _pParentUI);
public:
	// UI 타입의 Object의 Evnet관련 처리를 여기서 수행함
	void update();

};

