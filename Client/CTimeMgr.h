#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr)
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrequency;

	// FPS
	// 1프레임당 시간 (Delta Time)
public:
	void init();
};

