#include "pch.h"

#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

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

// Object �ϳ� ����
CObject g_obj;

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

	g_obj.SetPos(Vec2((float)m_ptResolution.x / 2, (float)m_ptResolution.y / 2));
	g_obj.SetScale(Vec2(100.f, 100.f));

	// TimeMgr �ʱ�ȭ
	CTimeMgr::GetInstance()->init();
	// KEYMgr �ʱ�ȭ
	CKeyMgr::GetInstance()->init();
	// SceneMgr �ʱ�ȭ
	CSceneMgr::GetInstance()->init();

	return S_OK;
}

HWND CCore::getHWND()
{
	return m_hWnd;
}

void CCore::progress()
{
	update();
	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD) {
		vPos.x -= 100 * CTimeMgr::GetInstance()->getDT();
	}

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD) {
		vPos.x += 100 * CTimeMgr::GetInstance()->getDT();
	}
	g_obj.SetPos(vPos);
}

void CCore::render()
{
	Rectangle(m_memhDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_memhDC,
		(int)(vPos.x - vScale.x / 2.f),
		(int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f),
		(int)(vPos.y + vScale.y / 2.f)
		);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memhDC, 0, 0, SRCCOPY);

}
