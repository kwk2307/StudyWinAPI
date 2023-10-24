#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr)
private:
	// ���� ī��Ʈ
	LARGE_INTEGER m_llCurCount;
	// ���� ī��Ʈ
	LARGE_INTEGER m_llPreCount;
	// �ʴ� �� �� �ִ� ī��Ʈ�� ��
	LARGE_INTEGER m_llFrequency;

	// 1�ʴ� ȣ��� ȸ��
	UINT m_iCallCnt;
	// Delta time
	double m_dDT;
	// Delta Time ����
	double m_dAccDT;

	// FPS
	// 1�����Ӵ� �ð� (Delta Time)

public:
	void init();
	void update();
	
	void (*ptrTimerEvent)(UINT, double);

	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }

	UINT GetCallCnt() { return m_iCallCnt; }
};

