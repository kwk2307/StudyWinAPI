#pragma once

// 1.������ �� Ű�Է� ����ȭ�� ����

// 2.Ű�Է� �̺�Ʈ ó�� TAP, HOlD ��

enum class KEY_STATE {
	NONE,	// �ȴ���
	TAP,	// �ѹ�����
	HOLD,	// ������ ������
	AWAY,	// �� ������ �����
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
	LBUTTON,
	RBUTTON,
	LAST,
};

struct tkeyinfo {

	bool bPrev;			// ���������ӿ� ���ȴ��� 
	KEY_STATE eState;	//Ű�� ����

};
class CKeyMgr
{
	SINGLE(CKeyMgr)

private:
	vector<tkeyinfo> m_Veckey;
	Vec2 m_vMousePos;

public:
	Vec2 GetMousePos() { return m_vMousePos; }

public:
	KEY_STATE GetKeyState(KEY _key);

public:
	void init();
	void update();
};

