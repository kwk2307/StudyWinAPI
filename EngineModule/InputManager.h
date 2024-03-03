#pragma once
enum class KeyState
{
	NONE,	// 안누름
	TAP,	// 한번눌림
	HOLD,	// 누르고 유지중
	AWAY,	// 막 눌림이 사라짐
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

private:
	InputManager();
	~InputManager();

public:
	static InputManager& GetInstanc() {
		static InputManager _InputManager;
		return _InputManager;
	}

	void Update();
	KeyState GetKeyState(Key InKey) { return vecKey[static_cast<int>(InKey)].state; }
	float GetXAxis();
	float GetYAxis();

private:
	std::vector<keyinfo> vecKey;
};

