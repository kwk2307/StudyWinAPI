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

public:
	void init();
	void update();

	KEY_STATE GetKeyState(KEY _key);
};

