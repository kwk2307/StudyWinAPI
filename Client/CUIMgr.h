#pragma once
class CUIMgr
{
	SINGLE(CUIMgr)
private:

public:
	// UI Ÿ���� Object�� Evnet���� ó���� ���⼭ ������
	void update();

	bool ClickEvent(CObject* _object);
};

