#include "pch.h"

#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

//CCore* CCore::g_pCore = nullptr;

//맴버 이니셜라이저
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

// Object 하나 생성
CObject g_obj;

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

	g_obj.SetPos(Vec2((float)m_ptResolution.x / 2, (float)m_ptResolution.y / 2));
	g_obj.SetScale(Vec2(100.f, 100.f));

	// TimeMgr 초기화
	CTimeMgr::GetInstance()->init();
	// KEYMgr 초기화
	CKeyMgr::GetInstance()->init();
	// SceneMgr 초기화
	CSceneMgr::GetInstance()->init();

	return S_OK;
}

HWND CCore::getHWND()
{
	return m_hWnd;
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
