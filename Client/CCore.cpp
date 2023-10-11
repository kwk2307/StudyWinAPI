#include "pch.h"

#include "CCore.h"
#include "CObject.h"

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

	g_obj.SetPos(Vec2((float)m_ptResolution.x / 2, (float)m_ptResolution.y / 2));
	g_obj.SetScale(Vec2(100.f, 100.f));

	return S_OK;
}

void CCore::progress()
{
	update();
	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		vPos.x -= 1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		vPos.x += 1;
	}
	g_obj.SetPos(vPos);
}

void CCore::render()
{

	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_hDC,
		(int)(vPos.x - vScale.x / 2.f),
		(int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f),
		(int)(vPos.y + vScale.y / 2.f)
		);
}
