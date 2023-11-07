#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	CObject* m_pOwner;
	map<wstring, CAnimation*> m_mAni;
	CAnimation* m_pCurAnim;

public:
	void SetOwner(CObject* obj) { m_pOwner = obj; }
	CObject* GetOwner() { return m_pOwner; }
	
	CAnimation* FindAnim(const wstring& _str);
	CAnimation* CreateAnim(const wstring& _str, CTexture* _pTex, Vec2 _vLT, Vec2 _vSize ,UINT _cnt);
	
	void SetCurAnim(const wstring& _str);

public:
	void update();
	void render(HDC _dc);

public:
	CAnimator();
	~CAnimator();
	CAnimator(const CAnimator& origin);

	friend class CObject;
};

