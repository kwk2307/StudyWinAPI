#pragma once
	

class CTexture;

class CResourceMgr
{
	SINGLE(CResourceMgr)
private:
	map<wstring, CTexture*> m_mapTex;

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* FIndTexture(const wstring& _strKey);
};

