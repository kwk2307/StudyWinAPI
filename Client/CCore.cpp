#include "pch.h"

#include "CCore.h"
#include "CObject.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"

//CCore* CCore::g_pCore = nullptr;

//맴버 이니셜라이저
CCore::CCore() :
	m_hWnd(0),
	m_ptResolution{},
	m_hDC(0),
	m_bitmap(0),
	m_memhDC(0),
	m_arrBrush{},
	m_arrPen{}
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memhDC);
	DeleteObject(m_bitmap);
	DeleteObject(m_arrPen[(UINT)PenType::RED]);
	DeleteObject(m_arrPen[(UINT)PenType::GREEN]);
	DeleteObject(m_arrPen[(UINT)PenType::BLUE]);
}

void CCore::CreateBrushPen()
{
	m_arrBrush[(UINT)BrushType::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	m_arrPen[(UINT)PenType::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PenType::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PenType::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	//해상도에 맞게 윈도우 크기 조정

	RECT rt = { 0,0,m_ptResolution.x,m_ptResolution.y };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	//SetWindowPos로 설정된
	SetWindowPos(m_hWnd, HWND_TOP, 0, 0, rt.right - rt.left, rt.bottom - rt.top, SWP_SHOWWINDOW);


	m_hDC = GetDC(m_hWnd);

	m_bitmap = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memhDC = CreateCompatibleDC(m_hDC);

	DeleteObject((HBITMAP)SelectObject(m_memhDC, m_bitmap));

	CreateBrushPen();

	// PathMgr 초기화
	CPathMgr::GetInstance()->init();

	// TimeMgr 초기화
	CTimeMgr::GetInstance()->init();
	CTimeMgr::GetInstance()->ptrTimerEvent = TimerEvent;

	// KEYMgr 초기화
	CKeyMgr::GetInstance()->init();

	// SceneMgr 초기화
	CSceneMgr::GetInstance()->init();
	
	// CollisionMgr 초기화
	CCollisionMgr::GetInstance()->init();

	// EventMgr 초기화
	CEventMgr::GetInstance()->init();

	// Camera 초기화
	CCamera::GetInstance()->init();

	return S_OK;
}


void CCore::progress()
{
	CTimeMgr::GetInstance()->update();
	
	CKeyMgr::GetInstance()->update();
	
	CSceneMgr::GetInstance()->update();
	
	CCollisionMgr::GetInstance()->update();

	CCamera::GetInstance()->update();

	Rectangle(m_memhDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	
	CSceneMgr::GetInstance()->render(m_memhDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memhDC, 0, 0, SRCCOPY);

	CEventMgr::GetInstance()->update();


}

void CCore::TimerEvent(UINT _iCallCnt, double _dDT)
{
	TCHAR szBuffer[1024];
	
	swprintf_s(szBuffer, L"FPS : %d, DT: %f", _iCallCnt, _dDT);

	SetWindowText(CCore::GetInstance()->getHWND(), szBuffer);
}
