#include "pch.h"

#include "CCore.h"

//CCore* CCore::g_pCore = nullptr;

//맴버 이니셜라이저
CCore::CCore() :
	m_hWnd(0),
	m_ptResolution{},
	m_hDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
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

	return S_OK;
}

void CCore::progress()
{
	update();
	render();
}

void CCore::update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
	
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {

	}

}

void CCore::render()
{
	Rectangle(m_hDC, 10, 10, 110, 110);
}
