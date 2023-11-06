#pragma once
class CRes;

struct FrameInfo {
	float fDuration;
	Vec2 m_vLT;			// 좌상단 위치 
	Vec2 m_vSize;		// 한 장당 크기 
};

class CAnimation
{
private:
	wstring m_strName;	// 애니메이션 이름 
	CRes* m_pTex;		// 텍스쳐 

	float m_fTime;		// 누적 시간
	vector<FrameInfo> m_vecFrameInfo;

public:
	void Create(const wstring& _str, CRes* _pRes, Vec2 _vLT, Vec2 _vSize, UINT _cnt);

public:
	CAnimation();
	~CAnimation();
};

