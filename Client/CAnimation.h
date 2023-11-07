#pragma once
class CTexture;
class CAnimator;

struct FrameInfo {
	float fDuration;
	Vec2 m_vLT;					// 좌상단 위치 
	Vec2 m_vSize;				// 한 장당 크기 
};

class CAnimation
{
private:
	CAnimator* m_pAnimator;
	wstring m_strName;			// 애니메이션 이름 
	CTexture* m_pTex;			// 텍스쳐 

	UINT m_iCnt;				// 현재 프레임 순서 
	float m_fTime;				// 누적 시간
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

