#pragma once
enum class KeyState
{
	NONE,	// �ȴ���
	TAP,	// �ѹ�����
	HOLD,	// ������ ������
	AWAY,	// �� ������ �����
};

enum class Key {

	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	A,
	S,
	D,
	F,
	ALT,
	CTRL,
	SPACE,
	ENTER,
	ESC,
	LBUTTON,
	RBUTTON,
	LAST,
};

struct keyinfo {
	bool prev = false;
	KeyState state = KeyState::NONE;
};

class InputManager
{
public:
	InputManager();
	
public:
	void Update();
	KeyState GetKeyState(Key InKey) const { return vecKey[static_cast<int>(InKey)].state; }

private:
	std::vector<keyinfo> vecKey;
};

