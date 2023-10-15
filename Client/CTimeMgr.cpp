#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr()
	:m_llCurCount{},
	m_llFrequency{},
	m_llPreCount{},
	m_dDT(0.),
	m_dAccDT(0.),
	m_iCallCnt(0)
{
}

CTimeMgr::~CTimeMgr() {

}

void CTimeMgr::init()
{
	QueryPerformanceCounter(&m_llCurCount);
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPreCount.QuadPart) / (double)m_llFrequency.QuadPart;

	m_llPreCount = m_llCurCount;

	m_iCallCnt++;
	m_dAccDT += m_dDT;

	if (m_dAccDT>=1.) {
		//윈도우 제목에 FPS 및 DeltaTime 표시

		//TCHAR szBuffer[1024];
		//swprintf_s(szBuffer, L"FPS : %d, DT: %f", m_iCallCnt, m_dDT);

		//SetWindowText(CCore::GetInstance()->getHWND(), szBuffer);

		//m_dAccDT = 0.;
		//m_iCallCnt = 0;
	}
}

double CTimeMgr::getDT()
{
	return m_dDT;
}

float CTimeMgr::getfDT()
{
	return (float)m_dDT;
}


 
