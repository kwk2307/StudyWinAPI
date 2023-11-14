#pragma once
class CUIMgr
{
	SINGLE(CUIMgr)
private:

public:
	// UI 타입의 Object의 Evnet관련 처리를 여기서 수행함
	void update();

	bool ClickEvent(CObject* _object);
};

