#pragma once
class CTexture;
class CAnimator;

struct FrameInfo {
	float fDuration;
	Vec2 m_vLT;					// �»�� ��ġ 
	Vec2 m_vSize;				// �� ��� ũ�� 
};

class CAnimation
{
private:
	CAnimator* m_pAnimator;
	wstring m_strName;			// �ִϸ��̼� �̸� 
	CTexture* m_pTex;			// �ؽ��� 

	UINT m_iCnt;				// ���� ������ ���� 
	float m_fTime;				// ���� �ð�
	vector<FrameInfo> m_vecFrameInfo;

public:
	void SetAnimator(CAnimator* _Animator) { m_pAnimator = _Animator; }

public:
	void Create(const wstring& _str, CTexture* _pTexture, Vec2 _vLT, Vec2 _vSize, UINT _cnt);

public:
	void update();
	void render(HDC _dc);

public:
	CAnimation();
	~CAnimation();
};

