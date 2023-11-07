#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr():
	ptrTimerEvent(nullptr),
	m_llCurCount{0,},
	m_llFrequency{0,},
	m_llPreCount{0,},
	m_dDT(0),
	m_dAccDT(0),
	m_iCallCnt(0)
{
}

CTimeMgr::~CTimeMgr() {

}

void CTimeMgr::init()
{
	QueryPerformanceCounter(&m_llCurCount);
	//ù �������� PreCountPart�� ����. �׷��� ������ �ʱ�ȭ ������ �����ɷ� �־��ش�.
	QueryPerformanceCounter(&m_llPreCount);

	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_dDT = (double)(m_llCurCount.QuadPart - m_llPreCount.QuadPart) / (double)m_llFrequency.QuadPart;

	m_llPreCount = m_llCurCount;

	m_iCallCnt++;
	m_dAccDT += m_dDT;

	if (m_dAccDT >= 1.) {
		//������ ���� FPS �� DeltaTime ǥ��

		ptrTimerEvent(m_iCallCnt, m_dDT);

		m_dAccDT = 0.;
		m_iCallCnt = 0;
	}
}



 
