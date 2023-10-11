#include "pch.h"
#include "CTimeMgr.h"


CTimeMgr::CTimeMgr()
	:m_llCurCount{},
	m_llPrequency{}
{

}

CTimeMgr::~CTimeMgr() {

}

void CTimeMgr::init()
{
	QueryPerformanceCounter(&m_llCurCount);
	QueryPerformanceFrequency(&m_llPrequency);
}
