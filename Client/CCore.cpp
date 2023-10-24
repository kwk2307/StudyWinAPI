#include "pch.h"

#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"

//CCore* CCore::g_pCore = nullptr;

//�ɹ� �̴ϼȶ�����
CCore::CCore() :
	m_hWnd(0),
	m_ptResolution{},
	m_hDC(0),
	m_bitmap(0),
	m_memhDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memhDC);
	DeleteObject(m_bitmap);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	//�ػ󵵿� �°� ������ ũ�� ����

	RECT rt = { 0,0,m_ptResolution.x,m_ptResolution.y };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	//SetWindowPos�� ������
	SetWindowPos(m_hWnd, HWND_TOP, 0, 0, rt.right - rt.left, rt.bottom - rt.top, SWP_SHOWWINDOW);

	m_hDC = GetDC(m_hWnd);

	m_bitmap = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memhDC = CreateCompatibleDC(m_hDC);

	DeleteObject((HBITMAP)SelectObject(m_memhDC, m_bitmap));

	// PathMgr �ʱ�ȭ
	CPathMgr::GetInstance()->init();

	// TimeMgr �ʱ�ȭ
	CTimeMgr::GetInstance()->init();
	CTimeMgr::GetInstance()->ptrTimerEvent = TimerEvent;

	// KEYMgr �ʱ�ȭ
	CKeyMgr::GetInstance()->init();

	// SceneMgr �ʱ�ȭ
	CSceneMgr::GetInstance()->init();

	return S_OK;
}


void CCore::progress()
{
	CTimeMgr::GetInstance()->update();
	CKeyMgr::GetInstance()->update();
	CSceneMgr::GetInstance()->update();
	
	Rectangle(m_memhDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	
	CSceneMgr::GetInstance()->render(m_memhDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memhDC, 0, 0, SRCCOPY);
}

void CCore::TimerEvent(UINT _iCallCnt, double _dDT)
{
	TCHAR szBuffer[1024];
	swprintf_s(szBuffer, L"FPS : %d, DT: %f", _iCallCnt, _dDT);

	SetWindowText(CCore::GetInstance()->getHWND(), szBuffer);

}
