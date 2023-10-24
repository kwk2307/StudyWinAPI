#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr)
private:
	// 현재 카운트
	LARGE_INTEGER m_llCurCount;
	// 이전 카운트
	LARGE_INTEGER m_llPreCount;
	// 초당 셀 수 있는 카운트의 양
	LARGE_INTEGER m_llFrequency;

	// 1초당 호출된 회수
	UINT m_iCallCnt;
	// Delta time
	double m_dDT;
	// Delta Time 누적
	double m_dAccDT;

	// FPS
	// 1프레임당 시간 (Delta Time)

public:
	void init();
	void update();
	
	void (*ptrTimerEvent)(UINT, double);

	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }

	UINT GetCallCnt() { return m_iCallCnt; }
};

