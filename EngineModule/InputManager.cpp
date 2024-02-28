#include "Precompiled.h"

int KeyMap[(int)Key::LAST] = {
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

InputManager::InputManager()
{
	for (int i = 0; i < (int)Key::LAST; ++i) {
		vecKey.push_back(keyinfo{ false, KeyState::NONE });
	}
}

void InputManager::Update()
{
	// 윈도우가 포커스 상태가 아닌경우 키 입력이 일어나지 않아야 한다.
	// 이를 처리하기 위해 윈도우 핸들러를 받아온다.
	HWND hWnd = GetFocus();

	if (hWnd != nullptr) {

		for (int i = 0; i < static_cast<int>(Key::LAST); ++i) {
			if (GetAsyncKeyState(KeyMap[i]) & 0x8000) {
				if (vecKey[i].prev) {
					vecKey[i].state = KeyState::HOLD;
				}
				else {
					vecKey[i].state = KeyState::TAP;
				}
				vecKey[i].prev = true;
			}
			else {
				if (vecKey[i].prev) {
					vecKey[i].state = KeyState::AWAY;
				}
				else {
					vecKey[i].state = KeyState::NONE;
				}
				vecKey[i].prev = false;
			}
		}
	}
	else {

	}
}
