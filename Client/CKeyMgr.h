#pragma once

// 1.프레임 내 키입력 동기화를 위함

// 2.키입력 이벤트 처리 TAP, HOlD 등

enum class KEY_STATE {
	NONE,	// 안누름
	TAP,	// 한번눌림
	HOLD,	// 누르고 유지중
	AWAY,	// 막 눌림이 사라짐
};

enum class KEY {

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
	LAST,
};

struct tkeyinfo {

	bool bPrev;			// 이전프레임에 눌렸는지 
	KEY_STATE eState;	//키의 상태

};
class CKeyMgr
{
	SINGLE(CKeyMgr)

private:
	vector<tkeyinfo> m_Veckey;

public:
	void init();
	void update();

	KEY_STATE GetKeyState(KEY _key);
};

