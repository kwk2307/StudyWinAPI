#pragma once
class CRes;

struct FrameInfo {
	float fDuration;
	Vec2 m_vLT;			// �»�� ��ġ 
	Vec2 m_vSize;		// �� ��� ũ�� 
};

class CAnimation
{
private:
	wstring m_strName;	// �ִϸ��̼� �̸� 
	CRes* m_pTex;		// �ؽ��� 

	float m_fTime;		// ���� �ð�
	vector<FrameInfo> m_vecFrameInfo;

public:
	void Create(const wstring& _str, CRes* _pRes, Vec2 _vLT, Vec2 _vSize, UINT _cnt);

public:
	CAnimation();
	~CAnimation();
};

