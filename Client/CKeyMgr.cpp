#include "pch.h"
#include "CKeyMgr.h"

CKeyMgr::CKeyMgr() {

};
CKeyMgr::~CKeyMgr() {

};

int g_arrKeyMap[(int)KEY::LAST] =  {
	VK_LEFT, //LEFT,
	VK_RIGHT, //RIGHT,
	VK_UP, //UP,
	VK_DOWN, //DOWN,
	'Q',//Q,
	'W',//W,
	'E',//E,
	'R',//R,
	'A',//A,
	'S',//S,
	'D',//D,
	'F',//F,
	VK_MENU, //ALT,
	VK_CONTROL, //CTRL,
	VK_SPACE, //SPACE,
	VK_RETURN, //ENTER,
	VK_ESCAPE, //ESC,
	VK_LBUTTON, 
	VK_RBUTTON,
	//LAST,
};


void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i) {
		m_Veckey.push_back(tkeyinfo{false, KEY_STATE::NONE});
	}
}

void CKeyMgr::update()
{
	HWND hWnd = GetFocus();
	if(hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i) {
			if (GetAsyncKeyState(g_arrKeyMap[i]) & 0x8000) {
				if (m_Veckey[i].bPrev) {
					m_Veckey[i].eState = KEY_STATE::HOLD;
				}
				else {
					m_Veckey[i].eState = KEY_STATE::TAP;
				}
				m_Veckey[i].bPrev = true;
			}
			else {
				if (m_Veckey[i].bPrev) {
					m_Veckey[i].eState = KEY_STATE::AWAY;
				}
				else {
					m_Veckey[i].eState = KEY_STATE::NONE;
				}
				m_Veckey[i].bPrev = false;
			}
		}
	}
	else {
		for (int i = 0; i < (int)KEY::LAST; ++i) {
			
			if (m_Veckey[i].eState == KEY_STATE::HOLD || m_Veckey[i].eState == KEY_STATE::TAP) {
				m_Veckey[i].eState = KEY_STATE::AWAY;
			}
			else if (m_Veckey[i].eState == KEY_STATE::AWAY){
				m_Veckey[i].eState = KEY_STATE::NONE;
			}
			m_Veckey[i].bPrev = false;
		}
	}
}

KEY_STATE CKeyMgr::GetKeyState(KEY _key)
{
	return m_Veckey[(int)_key].eState;
}
