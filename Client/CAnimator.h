#pragma once

class CObject;
class CAnimation;
class CRes;

class CAnimator
{
private:
	CObject* m_pOwner;
	map<wstring, CAnimation*> m_mAni;
public:
	void SetOwner(CObject* obj) { m_pOwner = obj; }
	
	CAnimation* FindAnim(const wstring& _str);
	CAnimation* CreateAnim(const wstring& _str, CRes* _pRes, Vec2 _vLT, Vec2 _vSize ,UINT _cnt);

public:
	CAnimator();
	~CAnimator();
	CAnimator(const CAnimator& origin);
};

