#pragma once
	

class CTexture;
class CRes;

class CResourceMgr
{
	SINGLE(CResourceMgr)
private:
	map<wstring, CRes*> m_mRes;

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* FIndTexture(const wstring& _strKey);
};

